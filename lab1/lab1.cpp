#include <iostream>
#include "vector.hpp"
#include "kv_struct.hpp"
#include "sort.hpp"
#include "parser.hpp"

int main() {
    TVector<TMD5String*> elems;
    Parser(elems);

    radix_sort(elems);

    for (unsigned int i = 0; i < elems.Size(); ++i) {
        std::cout << elems[i]->GetHexKey() << '\t' << elems[i]->GetValue() << std::endl;
    }
}
