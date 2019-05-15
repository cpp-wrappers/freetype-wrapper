#pragma once

#include "freetype_fwd.hpp"

namespace freetype {

enum class render_mode {
    normal = FT_RENDER_MODE_NORMAL,
    light = FT_RENDER_MODE_LIGHT,
    mono = FT_RENDER_MODE_MONO,
    lcd = FT_RENDER_MODE_LCD,
    lcd_v = FT_RENDER_MODE_LCD_V
};

}