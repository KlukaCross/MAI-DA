#ifndef KV_STRUCT_HPP
#define KV_STRUCT_HPP
#include <string>

const unsigned int HEX_BYTES_NUMBER = 32;
const unsigned int VALUE_BYTES_NUMBER = 64;

class TMD5String {
private:
    unsigned __int128 HexToInt(char c);
    char IntToHex(unsigned __int128 c);
    unsigned __int128 HexToInt128(std::string& st);
    void Int128ToHex(unsigned __int128 number, char st[HEX_BYTES_NUMBER]);
    unsigned __int128 key;
    char value[VALUE_BYTES_NUMBER];
public:
    TMD5String(std::string& key, std::string& value);
    unsigned __int128 GetIntKey();
    std::string GetHexKey();
    std::string GetValue();
};

#endif //KV_STRUCT_HPP
