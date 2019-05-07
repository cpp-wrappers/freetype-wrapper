#pragma once

#include <string>
#include "../freetype_fwd.hpp"
#include <stdexcept>

namespace freetype {

namespace internal {
    struct freetype_error : public std::runtime_error {
        freetype_error(const char* what)
        :std::runtime_error(what) {}
    };

    const char* error_string(int error) {
        return FT_Error_String(error);
    }

    void check_for_error(int error_code) {
        const char* error = error_string(error_code);
        if(error)
            throw freetype_error(error);
    }
}
}