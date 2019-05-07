#pragma once

#include "freetype_fwd.hpp"

namespace freetype {
    class glyph_slot;

    class glyph_metrics {
        friend glyph_slot;
        FT_Glyph_Metrics handle;

        glyph_metrics(FT_Glyph_Metrics handle) : handle{ handle } {}
    public:
        glyph_metrics(const glyph_metrics&) = default;
        glyph_metrics& operator=(const glyph_metrics&) = default;

        inline long width() {return handle.width;}
        inline long height() {return handle.height;}
        inline long horizontal_bearing_x() {return handle.horiBearingX;}
        inline long horizontal_bearing_y() {return handle.horiBearingY;}
        inline long horizontal_advance() {return handle.horiAdvance;}
        inline long vertical_bearing_x() {return handle.vertBearingX;}
        inline long vertical_bearing_y() {return handle.vertBearingY;}
        inline long vertical_advance() {return handle.vertAdvance;}
    };
}