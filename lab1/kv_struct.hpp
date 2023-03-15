#ifndef LAB1_KV_STRUCT_HPP
#define LAB1_KV_STRUCT_HPP
#include <string>

const int HEX_BYTES_NUMBER = 32;
const int VALUE_BYTES_NUMBER = 64;

class TMD5String {
private:
    unsigned __int128 hex_to_int(char c);
    char int_to_hex(unsigned __int128 c);
    unsigned __int128 hex_to_int128(const char st[HEX_BYTES_NUMBER]);
    void int128_to_hex(unsigned __int128 number, char st[HEX_BYTES_NUMBER]);
    unsigned __int128 key;
    char value[VALUE_BYTES_NUMBER];
public:
    TMD5String(const char key[HEX_BYTES_NUMBER], const char value[VALUE_BYTES_NUMBER]);
    unsigned __int128 GetIntKey();
    std::string GetHexKey();
    std::string GetValue();
};

#endif //LAB1_KV_STRUCT_HPP
