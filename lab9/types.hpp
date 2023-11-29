#ifndef LAB9_TYPES_HPP
#define LAB9_TYPES_HPP

#include <vector>
#include <exception>

typedef std::vector<std::vector<int>> TMatrix;

class TNegativeCycle : public std::exception {};

#endif //LAB9_TYPES_HPP
