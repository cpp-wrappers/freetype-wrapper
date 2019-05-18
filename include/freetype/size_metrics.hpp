#pragma once

#include "freetype_fwd.hpp"

namespace freetype {
    class size_metrics {
        friend class size;
        
        FT_Size_Metrics handle;

        size_metrics(FT_Size_Metrics handle)
        :handle{ handle } {}
    public:
        template<class Vec2>
        Vec2 ppem() {
            return {x_ppem(), y_ppem()};
        }

        u_short x_ppem() {
            return handle.x_ppem;
        }

        u_short y_ppem() {
            return handle.y_ppem;
        }

        long height() {
            return handle.height;
        }
	};
}