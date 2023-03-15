#include "sort.hpp"
#include <cmath>

const unsigned int KEY_BITS = 128;
const unsigned int MASK_SIZE = 8;

void counting_sort(TVector<TMD5String*> &elems, unsigned __int128 mask, size_t shift_count) {
    if (elems.Empty()) {
        return;
    }
    size_t max_elem = std::pow(2, MASK_SIZE);
    TVector<size_t> tmp(max_elem, 0);

    for (unsigned int i = 0; i < elems.Size(); ++i) {
        unsigned __int128 sort_key = (elems[i]->GetIntKey() & mask) >> (shift_count*MASK_SIZE);
        ++tmp[sort_key];
    }

    for (unsigned int i = 1; i < tmp.Size(); ++i) {
        tmp[i] += tmp[i-1];
    }

    TVector<TMD5String*> res(elems.Size(), nullptr);
    for (int i = elems.Size() - 1; i >= 0; --i) {
        unsigned __int128 sort_key = (elems[i]->GetIntKey() & mask) >> (shift_count*MASK_SIZE);
        size_t pos = tmp[sort_key]--;
        res[pos-1] = elems[i];
    }

    elems = std::move(res);
}

void radix_sort(TVector<TMD5String*> &elems) {
    unsigned __int128 mask = 1;
    for (unsigned int i = 0; i < MASK_SIZE-1; ++i) {
        mask = (mask << 1) | 1;
    }
    for (unsigned int i = 0; i < KEY_BITS/MASK_SIZE; ++i) {
        counting_sort(elems, mask, i);
        mask <<= MASK_SIZE;
    }
}
