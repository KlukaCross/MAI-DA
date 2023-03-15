#include "sort.hpp"
#include <cmath>

const unsigned int KEY_BITS = 128;
const unsigned int MASK_SIZE = 16;

void counting_sort(TVector<TMD5String*> &elems, TVector<TMD5String*> &result, unsigned __int128 mask, size_t shift_count,
                   size_t max_elem)
{
    if (elems.Empty()) {
        return;
    }
    TVector<size_t> tmp(max_elem, 0);

    for (unsigned int i = 0; i < elems.Size(); ++i) {
        unsigned __int128 sort_key = (elems[i]->GetIntKey() & mask) >> (shift_count*MASK_SIZE);
        ++tmp[sort_key];
    }

    for (unsigned int i = 1; i < tmp.Size(); ++i) {
        tmp[i] += tmp[i-1];
    }

    for (int i = elems.Size() - 1; i >= 0; --i) {
        unsigned __int128 sort_key = (elems[i]->GetIntKey() & mask) >> (shift_count*MASK_SIZE);
        size_t pos = tmp[sort_key]--;
        result[pos-1] = elems[i];
    }
}

void radix_sort(TVector<TMD5String*> &elems) {
    unsigned __int128 mask = 1;
    for (unsigned int i = 0; i < MASK_SIZE-1; ++i) {
        mask = (mask << 1) | 1;
    }
    size_t max_elem = std::pow(2, MASK_SIZE);
    TVector<TMD5String*> tmp(elems.Size(), nullptr);
    for (unsigned int i = 0; i < KEY_BITS/MASK_SIZE; ++i) {
        if ((i & 1) == 0) {
            counting_sort(elems, tmp, mask, i, max_elem);
        } else {
            counting_sort(tmp, elems, mask, i, max_elem);
        }
        mask <<= MASK_SIZE;
    }
}
