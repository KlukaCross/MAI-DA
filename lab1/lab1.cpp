#include <iostream>
#include <fstream>
#include "vector.hpp"
#include "kv_struct.hpp"
#include "sort.hpp"

void FillZeros(char value[], size_t size) {
    for (int i = 0; i < size; ++i) {
        value[i] = '\0';
    }
}

int main() {
    TVector<TMD5String*> elems;
    char key[HEX_BYTES_NUMBER];
    char value[VALUE_BYTES_NUMBER];
    FILE* in = std::fopen("test", "r");
    while (std::fscanf(in, "%32s\t%s\n", key, value) > 0) {;
        TMD5String *elem = new TMD5String(key, value);
        elems.PushBack(elem);
        FillZeros(value, VALUE_BYTES_NUMBER);
    }
    radix_sort(elems);
    for (int i = 0; i < elems.Size(); ++i) {
        std::cout << elems[i]->GetHexKey() << '\t' << elems[i]->GetValue() << std::endl;
    }
}
