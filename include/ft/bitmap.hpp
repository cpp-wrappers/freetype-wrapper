#pragma once

#include <type_traits>
#include "pixel_mode.hpp"
#include "unified_math/vec2.hpp"

namespace ft {
    class glyph_slot;

    class bitmap {
        friend glyph_slot;
    
        void* handle;
        unsigned char* _data();
        bitmap(void* handle) : handle{ handle } {}
    public:

        unsigned char* data() {
            return _data();
        }
        
        template<uni::vec2ui Vec = uni::pair_ui>
        Vec size() { return {width(), height()}; }
        
        unsigned height() { return rows(); }
        unsigned rows();
        unsigned width();
        unsigned pitch();
        unsigned num_grays();

        pixel_mode pixel_mode();
    };
}