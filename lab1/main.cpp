#include <iostream>
#include "vector.hpp"
#include "kv_struct.hpp"

void test_vector() {
    TVector<int> v;
    v.PushBack(1);
    v.PushBack(2);
    v.PushBack(3);
    v.PushBack(4);
    std::cout << v.Back() << std::endl;
    v.PopBack();
    std::cout << v.Back() << std::endl;
    std::cout << v.Front() << std::endl;
    std::cout << v[1] << std::endl;
    v.Set(1, 28);
    std::cout << v.Get(1) << std::endl;
    std::cout << v.Size() << std::endl;
    v.PushBack(100);
    std::cout << v.Size() << std::endl;
}

void test_kv() {
    TMD5String kv("ffffffffffffffffffffffffffffffff", "ajhsgfdkjfds");
    std::cout << kv.GetHexKey() << std::endl;
}

int main() {
    test_kv();
    return 0;
}
