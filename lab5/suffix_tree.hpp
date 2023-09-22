#ifndef LAB5_SUFFIX_TREE_HPP
#define LAB5_SUFFIX_TREE_HPP
#include <string>
#include <unordered_map>

class TSuffixTree {
    struct TNode {
        size_t start;
        int *end;
        int suffixNumber;
        TNode *suffixLink;
        std::unordered_map<char, TNode *> children;

        TNode(size_t start, int *end, int suffixNumber, TNode *suffixLink)
        : start(start), end(end), suffixNumber(suffixNumber), suffixLink(suffixLink) {}
    };
// methods
public:
    TSuffixTree(std::string &text);
    int FindMinimumLineSectionSuffixNumber(int n);
private:
    void Build();
    int Dfs(TNode *node, int n);
// variables
private:
    std::string text;
    TNode *root = nullptr;
};


#endif //LAB5_SUFFIX_TREE_HPP
