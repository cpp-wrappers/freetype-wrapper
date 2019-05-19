#pragma once

#include "freetype_fwd.hpp"
#include <utility>
#include <memory>
#include "glyph_metrics.hpp"
#include "bitmap.hpp"

namespace freetype {

	class glyph_slot {
		friend class face;
		
		FT_GlyphSlot handle;
		bitmap bitmap_;
		glyph_metrics metrics;
		
		glyph_slot(FT_GlyphSlot handle)
		:
		handle{handle},
		bitmap_{handle->bitmap},
		metrics{handle->metrics} {}
	public:
		glyph_slot(glyph_slot&& g)
		:
		bitmap_{std::move(g.bitmap_)},
		metrics{std::move(g.metrics)}
		{
			handle = std::exchange(g.handle, nullptr);
		}

		glyph_slot& operator=(glyph_slot&& g) {
			handle = std::exchange(g.handle, nullptr);
			return *this;
		}

	public:
		inline bitmap& get_bitmap() { return bitmap_; }
		inline glyph_metrics& get_metrics() { return metrics; }

		inline int bitmap_left() { return handle->bitmap_left; }
		inline int bitmap_top() { return handle->bitmap_top; }
	};
}