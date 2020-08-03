#pragma once

#include <string>
#include "freetype_fwd.hpp"
#include <stdexcept>
#include <charconv>

namespace ft {

struct error : public std::runtime_error {
    error(const char* what)
    :
    std::runtime_error(what) {}
};

inline void check_for_error(int error_code) {
    if(!error_code)
        return;

    if(auto str = FT_Error_String(error_code))
        throw error{str};
    else {
        char arr[10];
        auto [last, err] = std::to_chars(arr, arr+10, error_code, 16);
        throw error{std::string{arr, last}.c_str()};
    }
}

}