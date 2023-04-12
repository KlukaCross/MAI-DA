#pragma once

#include <exception>

class TCustomException : public std::exception {};

class TKeyAlreadyExists : public TCustomException {
public:
    const char *what() const noexcept {
        return "Exist";
    }
};

class TNoSuchKey : public TCustomException {
public:
    const char *what() const noexcept {
        return "NoSuchWord";
    }
};
