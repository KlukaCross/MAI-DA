#ifndef LAB9_TYPES_HPP
#define LAB9_TYPES_HPP

#include <vector>
#include <unordered_map>
#include <exception>

struct TNode {
    int v;
    long w;
    TNode(int v, long w) : v(v), w(w) {};
    TNode() {};
};

typedef std::unordered_map<int, std::vector<TNode>> TGraph;

class TNegativeCycle : public std::exception {};

#endif //LAB9_TYPES_HPP
