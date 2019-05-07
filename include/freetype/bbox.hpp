#pragma once

#include "freetype_fwd.hpp"

namespace freetype {
	class bbox {
		friend class face;

		FT_BBox handle;

		bbox(FT_BBox handle):handle{ handle }{}
	public:
	
		inline long x_min() { return handle.xMin; }
		inline long y_min() { return handle.yMin; }
		inline long x_max() { return handle.xMax; }
		inline long y_max() { return handle.yMax; }
	};
}