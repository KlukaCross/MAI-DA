#include "kv_struct.hpp"

const size_t TRANSFORM_MASK_SIZE = 4;

unsigned __int128 TMD5String::hex_to_int(char c) {
    if (c <= '9')
        return c - '0';
    else if (c >= 'a' && c <= 'f')
        return 10 + c - 'a';
    return 0;
}

char TMD5String::int_to_hex(__uint128_t c) {
    if (c < 10)
        return '0' + c;
    else if (c > 9 && c < 16)
        return 'a' + c - 10;
    return '0';
}

unsigned __int128 TMD5String::hex_to_int128(std::string& st) {
    unsigned __int128 number = 0;
    for (unsigned int i = 0; i < HEX_BYTES_NUMBER-1; ++i) {
        unsigned __int128 hex = hex_to_int(st[i]);
        number = (number | hex) << TRANSFORM_MASK_SIZE;
    }
    unsigned __int128 hex = hex_to_int(st[HEX_BYTES_NUMBER-1]);
    number |= hex;
    return number;
}

void TMD5String::int128_to_hex(__uint128_t number, char st[HEX_BYTES_NUMBER]) {
    unsigned __int128 mask = 1;
    for (unsigned int i = 0; i < TRANSFORM_MASK_SIZE-1; ++i) {
        mask = (mask << 1) | 1;
    }
    for (unsigned int i = 1; i <= HEX_BYTES_NUMBER; ++i) {
        unsigned __int128 hex = number & mask;
        number >>= 4;
        st[HEX_BYTES_NUMBER-i] = int_to_hex(hex);
    }
}

TMD5String::TMD5String(std::string& key, std::string& value) {
    this->key = hex_to_int128(key);
    for (unsigned int i = 0; i < VALUE_BYTES_NUMBER; ++i) {
        if (value.size() <= i) {
            this->value[i] = '\0';
        } else {
            this->value[i] = value[i];
        }
    }
}

unsigned __int128 TMD5String::GetIntKey() {
    return this->key;
}

std::string TMD5String::GetHexKey() {
    char st[HEX_BYTES_NUMBER];
    int128_to_hex(key, st);
    return std::string(st, HEX_BYTES_NUMBER);
}

std::string TMD5String::GetValue() {
    unsigned int value_size = VALUE_BYTES_NUMBER;
    for (unsigned int i = 0; i < VALUE_BYTES_NUMBER; ++i) {
        if (value[i] == '\0') {
            value_size = i;
            break;
        }
    }
    return std::string(value, value_size);
}

