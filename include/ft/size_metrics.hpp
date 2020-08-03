#pragma once

namespace freetype {
    class size_metrics {
        friend class size;
        
        FT_Size_Metrics handle;

        size_metrics(FT_Size_Metrics handle)
        :handle{ handle } {}
    public:
        template<class Vec2>
        Vec2 ppem() const {
            return {x_ppem(), y_ppem()};
        }

        u_short x_ppem() const {
            return handle.x_ppem;
        }

        u_short y_ppem() const {
            return handle.y_ppem;
        }

        long height() const {
            return handle.height;
        }
	};
}