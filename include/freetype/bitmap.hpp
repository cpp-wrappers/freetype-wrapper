#pragma once

#include "freetype_fwd.hpp"
#include <type_traits>
#include "pixel_mode.hpp"

namespace freetype {
    class glyph_slot;

    class bitmap {
        friend glyph_slot;
    
        FT_Bitmap handle;

        bitmap(FT_Bitmap handle) : handle{ handle } {}
    public:
        bitmap(const bitmap&) = delete;

        template<class T>
        inline std::enable_if_t<sizeof(T) == 1, T*> data() { return (T*)handle.buffer; }
        inline unsigned rows() { return handle.rows; }
        inline unsigned width() { return handle.width; }
        inline unsigned pitch() { return handle.pitch; }
        inline pixel_mode pixel_mode() { return {handle.pixel_mode}; }
    };
}