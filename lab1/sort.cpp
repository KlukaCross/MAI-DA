#include "sort.hpp"
#include <cmath>

const unsigned int KEY_BITS = 128;
const unsigned int MASK_SIZE = 16;

void CountingSort(TVector<TMD5String*> &elems, TVector<TMD5String*> &result, unsigned __int128 mask, size_t shift_count)
{
    if (elems.Empty()) {
        return;
    }
    TVector<size_t> tmp(mask+1, 0);

    for (unsigned int i = 0; i < elems.Size(); ++i) {
        unsigned __int128 sort_key = elems[i]->GetIntKey() >> (shift_count * MASK_SIZE);
        sort_key = sort_key & mask;
        ++tmp[sort_key];
    }

    for (unsigned int i = 1; i < tmp.Size(); ++i) {
        tmp[i] += tmp[i-1];
    }

    for (int i = elems.Size() - 1; i >= 0; --i) {
        unsigned __int128 sort_key = elems[i]->GetIntKey() >> (shift_count * MASK_SIZE);
        sort_key = sort_key & mask;
        size_t pos = tmp[sort_key]--;
        result[pos - 1] = elems[i];
    }
}

void RadixSort(TVector<TMD5String*> &elems) {
    unsigned __int128 mask = std::pow(2, MASK_SIZE)-1;

    TVector<TMD5String*> tmp(elems.Size(), nullptr);

    for (unsigned short i = 0; i < KEY_BITS / MASK_SIZE; ++i) {
        if ((i & 1) == 0) {
            CountingSort(elems, tmp, mask, i);
        } else {
            CountingSort(tmp, elems, mask, i);
        }
    }
}
