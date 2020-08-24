#pragma once

#include <type_traits>
#include "pixel_mode.hpp"

namespace ft {
    class glyph_slot;

    class bitmap {
        friend glyph_slot;
    
        void* handle;
        unsigned char* _data();
        bitmap(void* handle) : handle{ handle } {}
    public:

        template<class T=unsigned char>
        std::enable_if_t<sizeof(T) == 1, T*>
        data() {
            return (T*)_data();
        }
        
        template<class Vec2>
        Vec2 dimension() {
            return {width(), rows()};
        }
        
        unsigned rows();
        unsigned width();
        unsigned pitch();
        unsigned num_grays();

        pixel_mode pixel_mode();
    };
}