#pragma once

#include "freetype_fwd.hpp"
#include <stdexcept>

namespace freetype {

struct pixel_mode {
    const u_char token;

    constexpr u_char bits() {
        return bits_from_token(token);
    };

    static constexpr u_char bits_from_token(u_char token) {
        switch(token) {
            case FT_PIXEL_MODE_NONE : return 0;
            case FT_PIXEL_MODE_MONO : return 1;
            case FT_PIXEL_MODE_GRAY : return 8;
            case FT_PIXEL_MODE_GRAY2 : return 2;
            case FT_PIXEL_MODE_GRAY4 : return 4;
            case FT_PIXEL_MODE_LCD : return 8*3;
            case FT_PIXEL_MODE_LCD_V : return 8*3;
            case FT_PIXEL_MODE_BGRA : return 8*4;
            default : throw std::logic_error("invalid freetype pixel mode token");
        }
    }
};

// To be able to compare

constexpr pixel_mode none{FT_PIXEL_MODE_NONE};
constexpr pixel_mode mono{FT_PIXEL_MODE_MONO};
constexpr pixel_mode gray{FT_PIXEL_MODE_GRAY};
constexpr pixel_mode gray2{FT_PIXEL_MODE_GRAY2};
constexpr pixel_mode gray4{FT_PIXEL_MODE_GRAY4};
constexpr pixel_mode lcd{FT_PIXEL_MODE_LCD};
constexpr pixel_mode lcd_V{FT_PIXEL_MODE_LCD_V};
constexpr pixel_mode bgra{FT_PIXEL_MODE_BGRA};

}