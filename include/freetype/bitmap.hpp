#pragma once

#include "freetype_fwd.hpp"
#include <type_traits>
#include "pixel_mode.hpp"

namespace freetype {
    class glyph_slot;

    class bitmap {
        friend glyph_slot;
    
        FT_Bitmap& handle;

        bitmap(FT_Bitmap& handle) : handle{ handle } {}
    public:
        bitmap(bitmap&& r) = default;

        bitmap(const bitmap&) = delete;

        template<class T>
        std::enable_if_t<sizeof(T) == 1, T*>
        data() { return (T*)handle.buffer; }
        
        template<class Vec2>
        Vec2 size() {
            return {width(), rows()};
        }
        
        uint rows() { return handle.rows; }
        uint width() { return handle.width; }
        uint pitch() { return handle.pitch; }
        uint num_grays() { return handle.num_grays; }

        pixel_mode pixel_mode() {
            return internal::from_token(handle.pixel_mode); 
        }
    };
}