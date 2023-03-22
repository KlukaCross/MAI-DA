#ifndef KV_STRUCT_HPP
#define KV_STRUCT_HPP
#include <string>

const unsigned int HEX_BYTES_NUMBER = 32;
const unsigned int VALUE_BYTES_NUMBER = 64;
__extension__ using Tuint128 = unsigned __int128;

class TMD5String {
private:
    Tuint128 HexToInt(char c);
    char IntToHex(Tuint128 c);
    Tuint128 HexToInt128(std::string& st);
    void Int128ToHex(Tuint128 number, char st[HEX_BYTES_NUMBER]);
    Tuint128 key;
    char value[VALUE_BYTES_NUMBER];
public:
    TMD5String(std::string& key, std::string& value);
    Tuint128 GetIntKey();
    std::string GetHexKey();
    std::string GetValue();
};

#endif //KV_STRUCT_HPP
