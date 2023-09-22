#include "suffix_tree.hpp"

const char SENTINEL = '$';

TSuffixTree::TSuffixTree(std::string &text)
{
    text += SENTINEL;
    this->text = text;
    root = new TNode(0, new int(-1), -1, nullptr);
    Build();
}

void TSuffixTree::Build() {
    /* builds a tree using Ukkonen's algorithm */
    TNode *currentNode = root;
    size_t j = 0;
    size_t currentCharIndex = 0;
    size_t currentEdgeLength = 0;
    int *globalEnd = new int(-1);
    for (size_t i = 0; i < text.length(); ++i) {
        /* single phase algorithm (SPA) */
        TNode *lastCreatedNode = nullptr;
        (*globalEnd)++; // "add" a text[phase] to each leaf (rule 1)
        for (; j <= i;) {
            /* single extension algorithm (SEA) */
            if (currentEdgeLength == 0) { // starts from root
                currentCharIndex = i;
            }

            if (not currentNode->children.contains(text[currentCharIndex])) { // if edges do not start with currentCharIndex (rules 1, 2)
                currentNode->children[text[currentCharIndex]] = new TNode(i, globalEnd, j, root);
                if (lastCreatedNode) {
                    lastCreatedNode->suffixLink = currentNode;
                    lastCreatedNode = nullptr;
                }
            } else {
                TNode *nextNode = currentNode->children[text[currentCharIndex]];
                size_t nextEdgeLength = *(nextNode->end) - (nextNode->start) + 1;

                if (currentEdgeLength >= nextEdgeLength) {  // go down
                    currentCharIndex += nextEdgeLength;
                    currentEdgeLength -= nextEdgeLength;
                    currentNode = nextNode;
                    continue;
                }

                if (text[nextNode->start + currentEdgeLength] == text[i]) { // if edge starts with text[phase] (rule 3)
                    ++currentEdgeLength;
                    if (lastCreatedNode) {
                        lastCreatedNode->suffixLink = currentNode;
                    }
                    break;
                }

                // insert a new node inside the edge (rule 2)
                TNode *newNode = new TNode(nextNode->start, new int(nextNode->start + currentEdgeLength - 1), -1, root);
                currentNode->children[text[currentCharIndex]] = newNode;
                nextNode->start += currentEdgeLength;
                newNode->children[text[nextNode->start]] = nextNode;
                newNode->children[text[i]] = new TNode(i, globalEnd, j, root);
                if (lastCreatedNode and currentNode != root) {
                    lastCreatedNode->suffixLink = newNode;
                }
                lastCreatedNode = newNode;
            }

            if (currentNode == root) {
                if (currentEdgeLength) {
                    ++currentCharIndex;
                    --currentEdgeLength;
                }
            } else {
                currentNode = currentNode->suffixLink;
            }
            ++j;
        }
    }
}

int TSuffixTree::Dfs(TNode *node, int n) {
    if (not node) {
        return -1;
    }
    if ((*node->end) > n and node->suffixNumber != -1) {
        return node->suffixNumber;
    }
    if (node->children.empty()) {
        return -1;
    }
    char minChar = 'z'+1;
    for (auto &key: node->children) {
        if (key.first != '$' and key.first < minChar) {
            minChar = key.first;
        }
    }
    if (minChar == 'z'+1) {
        minChar = '$';
    }
    return Dfs(node->children[minChar], n);
}

int TSuffixTree::FindMinimumLineSectionSuffixNumber(int n) {
    return Dfs(root, n);
}
