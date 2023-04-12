#include "patricia.hpp"
#include "custom_exception.hpp"

void TPatricia::Add(const std::string &key, const uint64_t &value) {
    if (!root) {
        root = new TNode(key, value, 0);
        root->left = root;
        return;
    }

    TNode *foundedNode = Find(key);
    if (foundedNode->key == key) {
        throw TKeyAlreadyExists();
    }
    size_t newIndex = CalculateNewIndex(key, foundedNode->key);
    Insert(key, value, newIndex);
}

TPatricia::TNode *TPatricia::Find(const std::string &key) {
    if (!root) {
        return nullptr;
    }
    TNode *curNode = root->left;
    TNode *prevNode = root;

    while (curNode->index > prevNode->index) {
        size_t charPos = (curNode->index - 1) / CHAR_BIT_COUNT;
        char curChar = key.size() > charPos ? key[charPos] : '\0';
        uint8_t offset = (curNode->index - 1) % CHAR_BIT_COUNT;
        bool curBit = (curChar >> offset) & 1;

        prevNode = curNode;
        curNode = curBit ? curNode->right : curNode->left;
    }
    return curNode;
}

void TPatricia::Insert(const std::string &key, const uint64_t &value, const size_t &index) {
    TNode *curNode = root->left;
    TNode *prevNode = root;

    while (curNode->index > prevNode->index && curNode->index <= index) {
        size_t charPos = (curNode->index - 1) / CHAR_BIT_COUNT;
        char curChar = key.size() > charPos ? key[charPos] : '\0';
        uint8_t offset = (curNode->index - 1) % CHAR_BIT_COUNT;
        bool curBit = (curChar >> offset) & 1;

        prevNode = curNode;
        curNode = curBit ? curNode->right : curNode->left;
    }

    TNode *newNode = new TNode(key, value, index);

    if (prevNode->left == curNode) {
        prevNode->left = newNode;
    } else {
        prevNode->right = newNode;
    }

    char newChar = key[index / CHAR_BIT_COUNT];
    uint8_t offset = (index - 1) % CHAR_BIT_COUNT;
    bool newBit = (newChar >> offset) & 1;

    if (newBit) {
        newNode->right = newNode;
        newNode->left = curNode;
    } else {
        newNode->left = newNode;
        newNode->right = curNode;
    }
}

size_t TPatricia::CalculateNewIndex(const std::string &inputKey, const std::string &foundedKey) {
    for (size_t charPos = 0; charPos < KEY_MAX_SIZE; ++charPos) {
        size_t foundedChar = foundedKey.size() > charPos ? foundedKey[charPos] : '\0';
        size_t inputChar = inputKey.size() > charPos ? inputKey[charPos] : '\0';
        for (size_t i = 0; i < CHAR_BIT_COUNT; ++i) {
            bool foundedBit = (foundedChar >> i) & 1;
            bool inputBit = (inputChar >> i) & 1;
            if (foundedBit != inputBit) {
                size_t newIndex = charPos * CHAR_BIT_COUNT + i + 1;
                return newIndex;
            }
        }
    }
    return 0;
}

uint64_t TPatricia::At(const std::string &key) {
    TNode *foundedNode = Find(key);
    if (!foundedNode || foundedNode->key != key) {
        throw TNoSuchKey();
    }
    return foundedNode->value;
}

void TPatricia::Erase(const std::string &key) {
    if (!root) {
        throw TNoSuchKey();
    }
    // aNode - delete node, bNode - previous of delete node, cNode - pre-previous of delete Node
    auto [aNode, bNode, cNode] = FindABC(key);

    if (aNode->key != key) {
        throw TNoSuchKey();
    }

    if (aNode == root && root->left == root) { // if delete node is root and size == 1, then just delete it
        delete root;
        root = nullptr;
        return;
    }
    if (bNode == aNode) { // if delete node is leaf, then tie cNode with child of aNode
        if (cNode->right == aNode) {
            cNode->right = aNode->right == aNode ? aNode->left : aNode->right;
        } else {
            cNode->left = aNode->right == aNode ? aNode->left : aNode->right;
        }
        delete aNode;
        return;
    }

    // dNode - is bNode (unused), eNode - previous of bNode, fNode - pre-previous of bNode (unused)
    auto [dNode, eNode, fNode] = FindABC(bNode->key);

    // ... else bNode data moving to aNode data
    aNode->key = bNode->key;
    aNode->value = bNode->value;

    if (eNode == bNode) { // if bNode is leaf, then tie cNode with aNode
        if (cNode->right == bNode) {
            cNode->right = aNode;
        } else {
            cNode->left = aNode;
        }
    } else { // else tie cNode with child of bNode
        if (cNode->right == bNode) {
            cNode->right = bNode->right == aNode ? bNode->left : bNode->right;
        } else {
            cNode->left = bNode->right == aNode ? bNode->left : bNode->right;
        }
        if (eNode->right == bNode) { // ... and tie eNode with aNode
            eNode->right = aNode;
        } else {
            eNode->left = aNode;
        }
    }
    delete bNode;
}

std::tuple<TPatricia::TNode *, TPatricia::TNode *, TPatricia::TNode *> TPatricia::FindABC(const std::string &key) {
    TNode* curNode = root->left;
    TNode* prevNode = root;
    TNode* prevPrevNode = root;

    while (curNode->index > prevNode->index) {
        size_t charPos = (curNode->index - 1) / CHAR_BIT_COUNT;
        char curChar = charPos > key.size() ? '\0' : key[charPos];
        uint8_t offset = (curNode->index - 1) % CHAR_BIT_COUNT;
        bool curBit = (curChar >> offset) & 1;

        prevPrevNode = prevNode;
        prevNode = curNode;
        curNode = curBit ? curNode->right : curNode->left;
    }
    return std::make_tuple(curNode, prevNode, prevPrevNode);
}

TPatricia::~TPatricia() {
    Destroy();
}

void TPatricia::Destroy() {
    if (!root) {
        return;
    }
    if (root != root->left) {
        RecursiveDestroy(root->left);
    }
    delete root;
    root = nullptr;
}

void TPatricia::RecursiveDestroy(TNode *node) {
    if (node->left->index > node->index) {
        RecursiveDestroy(node->left);
    }
    if (node->right->index > node->index) {
        RecursiveDestroy(node->right);
    }

    delete node;
}

void TPatricia::Save(const std::string &path) {
    std::ofstream fout;
    fout.open(path, std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
    if (!root) {
        fout.close();
        return;
    }

    SaveData(root, fout);
    if (root != root->left) {
        RecursiveSave(root->left, fout);
    }
    fout.close();
}

void TPatricia::SaveData(const TPatricia::TNode *node, std::ofstream &stream) {
    std::string key = node->key;
    size_t keySize = key.size();
    uint64_t value = node->value;
    stream.write((char *) (&keySize), sizeof(size_t));
    stream.write(key.c_str(), sizeof(char) * keySize);
    stream.write((char *) (&value), sizeof(uint64_t));
}

void TPatricia::RecursiveSave(const TPatricia::TNode *node, std::ofstream &stream) {
    SaveData(node, stream);
    if (node->left->index > node->index) {
        RecursiveSave(node->left, stream);
    }
    if (node->right->index > node->index) {
        RecursiveSave(node->right, stream);
    }
}

void TPatricia::Load(const std::string &path) {
    std::ifstream fin;
    fin.open(path, std::ios_base::in | std::ios_base::binary);
    TNode* curNode;
    while ((curNode = LoadData(fin)) != nullptr) {
        Add(curNode->key, curNode->value);
        delete curNode;
    }
}

TPatricia::TNode *TPatricia::LoadData(std::ifstream &stream) {
    if (stream.eof()) {
        return nullptr;
    }
    size_t keySize;
    std::string key;
    uint64_t value;
    stream.read((char *) &keySize, sizeof(size_t));
    if (!stream) {
        return nullptr;
    }
    key.resize(keySize);
    stream.read(key.data(), sizeof(char) * keySize);
    stream.read((char *) &value, sizeof(sizeof(uint64_t)));
    TNode *node = new TNode(key, value, 0);
    return node;
}
