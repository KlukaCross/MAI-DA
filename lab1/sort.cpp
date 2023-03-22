#include "sort.hpp"
#include <cmath>

const unsigned int KEY_BITS = 128;
const unsigned int MASK_SIZE = 16;

void CountingSort(TVector<TMD5String*> &elems, TVector<TMD5String*> &result, Tuint128 mask, size_t shiftCount) {
    if (elems.Empty()) {
        return;
    }
    TVector<size_t> tmp(mask+1, 0);

    for (unsigned int i = 0; i < elems.Size(); ++i) {
        Tuint128 sortKey = elems[i]->GetIntKey() >> (shiftCount * MASK_SIZE);
        sortKey = sortKey & mask;
        ++tmp[sortKey];
    }

    for (unsigned int i = 1; i < tmp.Size(); ++i) {
        tmp[i] += tmp[i-1];
    }

    for (int i = elems.Size() - 1; i >= 0; --i) {
        Tuint128 sortKey = elems[i]->GetIntKey() >> (shiftCount * MASK_SIZE);
        sortKey = sortKey & mask;
        size_t pos = tmp[sortKey]--;
        result[pos - 1] = elems[i];
    }
}

void RadixSort(TVector<TMD5String*> &elems) {
    Tuint128 mask = std::pow(2, MASK_SIZE)-1;

    TVector<TMD5String*> tmp(elems.Size(), nullptr);

    for (unsigned short i = 0; i < KEY_BITS / MASK_SIZE; ++i) {
        if ((i & 1) == 0) {
            CountingSort(elems, tmp, mask, i);
        } else {
            CountingSort(tmp, elems, mask, i);
        }
    }
}
