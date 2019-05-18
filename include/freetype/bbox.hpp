#pragma once

#include "freetype_fwd.hpp"

namespace freetype {
	class bbox {
		friend class face;

		FT_BBox handle;

		bbox(FT_BBox handle):handle{ handle }{}
	public:

		template<class Vec2>
		Vec2 size() {
			return {x_max() - x_min(), y_max() - y_min()};
		}

		long x_min() { return handle.xMin; }
		long y_min() { return handle.yMin; }
		long x_max() { return handle.xMax; }
		long y_max() { return handle.yMax; }
	};
}