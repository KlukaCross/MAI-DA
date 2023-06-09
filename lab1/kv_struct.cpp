#include "kv_struct.hpp"

const size_t TRANSFORM_MASK_SIZE = 4;

Tuint128 TMD5String::HexToInt(char c) {
    if (c <= '9')
        return c - '0';
    else if (c >= 'a' && c <= 'f')
        return 10 + c - 'a';
    return 0;
}

char TMD5String::IntToHex(Tuint128 c) {
    if (c < 10)
        return '0' + c;
    else if (c > 9 && c < 16)
        return 'a' + c - 10;
    return '0';
}

Tuint128 TMD5String::HexToInt128(std::string& st) {
    Tuint128 number = 0;
    for (unsigned int i = 0; i < HEX_BYTES_NUMBER - 1; ++i) {
        Tuint128 hex = HexToInt(st[i]);
        number = (number | hex) << TRANSFORM_MASK_SIZE;
    }
    Tuint128 hex = HexToInt(st[HEX_BYTES_NUMBER - 1]);
    number |= hex;
    return number;
}

void TMD5String::Int128ToHex(Tuint128 number, char st[HEX_BYTES_NUMBER]) {
    Tuint128 mask = 1;
    for (unsigned int i = 0; i < TRANSFORM_MASK_SIZE - 1; ++i) {
        mask = (mask << 1) | 1;
    }
    for (unsigned int i = 1; i <= HEX_BYTES_NUMBER; ++i) {
        Tuint128 hex = number & mask;
        number >>= 4;
        st[HEX_BYTES_NUMBER-i] = IntToHex(hex);
    }
}

TMD5String::TMD5String(std::string& key, std::string& value) {
    this->key = HexToInt128(key);
    for (unsigned int i = 0; i < VALUE_BYTES_NUMBER; ++i) {
        if (value.size() <= i) {
            this->value[i] = '\0';
        } else {
            this->value[i] = value[i];
        }
    }
}

Tuint128 TMD5String::GetIntKey() {
    return this->key;
}

std::string TMD5String::GetHexKey() {
    char st[HEX_BYTES_NUMBER];
    Int128ToHex(key, st);
    return std::string(st, HEX_BYTES_NUMBER);
}

std::string TMD5String::GetValue() {
    unsigned int valueSize = VALUE_BYTES_NUMBER;
    for (unsigned int i = 0; i < VALUE_BYTES_NUMBER; ++i) {
        if (value[i] == '\0') {
            valueSize = i;
            break;
        }
    }
    return std::string(value, valueSize);
}

