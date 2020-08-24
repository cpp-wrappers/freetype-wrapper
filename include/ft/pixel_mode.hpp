#pragma once

#include <stdexcept>
#include <cstdint>

namespace ft {

struct pixel_mode {
    const uint8_t token;
    const uint8_t bits;

    bool operator==(const pixel_mode& pm) {
        return token==pm.token && bits == pm.bits;
    }
};

constexpr pixel_mode 
    none{1, 0}, mono{2, 1}, gray{3, 8}, gray2{4, 2},
    gray4{5, 4}, lcd{6, 8*3}, lcd_v{7, 8*3}, bgra{8, 8*4};

namespace internal
{

// TODO
constexpr pixel_mode from_token(uint8_t token) {
    switch(token) {
        case 0 : return none;
        case 1 : return mono;
        case 2 : return gray;
        case 3 : return gray2;
        case 4 : return gray4;
        case 5 : return lcd;
        case 6 : return lcd_v;
        case 7 : return bgra;
        default : throw std::logic_error("invalid freetype pixel mode token");
    }
}

}

}