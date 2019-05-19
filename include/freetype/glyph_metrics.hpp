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

        long width() const {return handle.width;}
        long height() const {return handle.height;}

        template<class Vec2>
        Vec2 size() const {
            return{width(), height()};
        }

        inline long horizontal_bearing_x() const {return handle.horiBearingX;}
        inline long horizontal_bearing_y() const {return handle.horiBearingY;}

        template<class Vec2>
        Vec2 horizontal_bearing() const {
            return{width(), height()};
        }

        inline long horizontal_advance() const {return handle.horiAdvance;}
        inline long vertical_bearing_x() const {return handle.vertBearingX;}
        inline long vertical_bearing_y() const {return handle.vertBearingY;}

        template<class Vec2>
        Vec2 vertical_bearing() const {
            return{width(), height()};
        }

        inline long vertical_advance() const {return handle.vertAdvance;}
    };
}