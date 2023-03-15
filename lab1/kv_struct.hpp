#ifndef LAB1_KV_STRUCT_HPP
#define LAB1_KV_STRUCT_HPP
#include <string>

const unsigned int HEX_BYTES_NUMBER = 32;
const unsigned int VALUE_BYTES_NUMBER = 64;

class TMD5String {
private:
    unsigned __int128 hex_to_int(char c);
    char int_to_hex(unsigned __int128 c);
    unsigned __int128 hex_to_int128(std::string& st);
    void int128_to_hex(unsigned __int128 number, char st[HEX_BYTES_NUMBER]);
    unsigned __int128 key;
    char value[VALUE_BYTES_NUMBER];
public:
    TMD5String(std::string& key, std::string& value);
    unsigned __int128 GetIntKey();
    std::string GetHexKey();
    std::string GetValue();
};

#endif //LAB1_KV_STRUCT_HPP
