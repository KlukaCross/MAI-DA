#ifndef SORT_HPP
#define SORT_HPP
#include "vector.hpp"
#include "kv_struct.hpp"

void counting_sort(TVector<TMD5String*> &elems, unsigned __int128 mask, size_t shift_count);

void radix_sort(TVector<TMD5String*> &elems);

#endif //SORT_HPP
