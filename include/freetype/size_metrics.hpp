#pragma once

#include "freetype_fwd.hpp"

namespace freetype {
    class size_metrics {
        friend class face;
        
        FT_Size_Metrics handle;

        size_metrics(FT_Size_Metrics handle)
        :handle{ handle } {}
    public:
        inline unsigned short x_ppem() {
            return handle.x_ppem;
        }

        inline unsigned short y_ppem() {
            return handle.y_ppem;
        }

        inline signed long height() {
            return handle.height;
        }
	};
}