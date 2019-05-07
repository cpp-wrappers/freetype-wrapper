#pragma once

#include "freetype_fwd.hpp"
#include <utility>
#include "glyph_metrics.hpp"
#include "bitmap.hpp"

namespace freetype {
	class face;

	class glyph_slot {
		friend class face;
		
		FT_GlyphSlot handle;
		
		glyph_slot(FT_GlyphSlot handle): handle{ handle } {}
		glyph_slot() {}
	public:
		glyph_slot(glyph_slot&& g) {
			handle = std::exchange(g.handle, nullptr);
		}
		glyph_slot& operator=(glyph_slot&& g) {
			handle = std::exchange(g.handle, nullptr);
			return *this;
		}

	public:
		void render();
		
		inline bitmap get_bitmap() { return handle->bitmap; }
		inline glyph_metrics get_metrics() { return handle->metrics; }

		inline int bitmap_left() { return handle->bitmap_left; }
		inline int bitmap_top() { return handle->bitmap_top; }
	};
}