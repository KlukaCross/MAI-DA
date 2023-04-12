#pragma once

#include <cstddef>
#include <string>
#include <tuple>
#include <fstream>

const uint8_t CHAR_BIT_COUNT = 8;
const size_t KEY_MAX_SIZE = 256;

class TPatricia {
    struct TNode {
        std::string key;
        uint64_t value;
        size_t index;
        TNode *left;
        TNode *right;

        TNode(const std::string &key, const uint64_t &value, const size_t &index)
        : key(key), value(value), index(index), left(nullptr), right(nullptr) {}
    };
// Methods
private:
    void Destroy();
    void RecursiveDestroy(TNode *node);
    void Insert(const std::string &key, const uint64_t &value, const size_t &index);
    size_t CalculateNewIndex(const std::string &inputKey, const std::string &foundedKey);
    TNode* Find(const std::string &key);
    std::tuple<TPatricia::TNode*, TPatricia::TNode*, TPatricia::TNode*> FindABC(const std::string &key);
    void SaveData(const TNode *node, std::ofstream &stream);
    void RecursiveSave(const TNode *node, std::ofstream &stream);
    TNode* LoadData(std::ifstream &stream);
public:
    ~TPatricia();
    void Add(const std::string &key, const uint64_t &value);
    void Erase(const std::string &key);
    uint64_t At(const std::string &key);
    void Save(const std::string &path);
    void Load(const std::string &path);
// Variables
private:
    TNode *root = nullptr;
};
