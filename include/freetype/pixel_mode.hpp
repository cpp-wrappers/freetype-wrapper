#pragma once

#include "freetype_fwd.hpp"
#include <stdexcept>

namespace freetype {

struct pixel_mode {
    const u_char token;
    const u_char bits;

    bool operator==(const pixel_mode& pm) {
        return token==pm.token && bits == pm.bits;
    }
}

none{FT_PIXEL_MODE_NONE, 0},
mono{FT_PIXEL_MODE_MONO, 1},
gray{FT_PIXEL_MODE_GRAY, 8},
gray2{FT_PIXEL_MODE_GRAY2, 2},
gray4{FT_PIXEL_MODE_GRAY4, 4},
lcd{FT_PIXEL_MODE_LCD, 8*3},
lcd_v{FT_PIXEL_MODE_LCD_V, 8*3},
bgra{FT_PIXEL_MODE_BGRA, 8*4};

namespace internal
{

pixel_mode from_token(u_char token) {
    switch(token) {
        case FT_PIXEL_MODE_NONE : return none;
        case FT_PIXEL_MODE_MONO : return mono;
        case FT_PIXEL_MODE_GRAY : return gray;
        case FT_PIXEL_MODE_GRAY2 : return gray2;
        case FT_PIXEL_MODE_GRAY4 : return gray4;
        case FT_PIXEL_MODE_LCD : return lcd;
        case FT_PIXEL_MODE_LCD_V : return lcd_v;
        case FT_PIXEL_MODE_BGRA : return bgra;
        default : throw std::logic_error("invalid freetype pixel mode token");
    }
}

}

}