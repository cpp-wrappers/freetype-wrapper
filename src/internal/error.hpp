#pragma once

#include <string>
#include "../freetype_fwd.hpp"
#include <stdexcept>
#include <charconv>

namespace freetype {

namespace internal {
    struct freetype_error : public std::runtime_error {
        freetype_error(const char* what)
        :
        std::runtime_error(what) {}
    };

    inline const char* error_string(int error) {
        return FT_Error_String(error);
    }

    inline void check_for_error(int error_code) {
        if(!error_code)
            return;

        if(auto str = error_string(error_code))
            throw freetype_error{str};
        else {
            char arr[10];
            auto [last, err] = std::to_chars(arr, arr+10, error_code, 16);
            throw freetype_error{std::string{arr, last}.c_str()};
        }
    }
}
}