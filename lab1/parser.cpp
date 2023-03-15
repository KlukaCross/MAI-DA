#include "parser.hpp"
#include <iostream>

void Parser(TVector<TMD5String*>& elems) {
    std::string line;
    while (std::getline(std::cin, line, '\n')) {
        if (line.size() < HEX_BYTES_NUMBER) {
            continue;
        }
        std::string key = line.substr(0, HEX_BYTES_NUMBER);;
        std::string value;
        if (line.size() > HEX_BYTES_NUMBER + 1) {
            value = line.substr(HEX_BYTES_NUMBER + 1, VALUE_BYTES_NUMBER);
        }
        TMD5String *elem = new TMD5String(key, value);
        elems.PushBack(elem);
    }
}