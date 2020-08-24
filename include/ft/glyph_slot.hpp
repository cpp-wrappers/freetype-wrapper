#pragma once

#include <utility>
#include <memory>
#include "render_mode.hpp"
#include "bitmap.hpp"

namespace ft {
	class glyph_slot {
		friend class face;
		void* handle;
		
		static void wrap(void* handle);
		glyph_slot(void* handle);

	public:
		glyph_slot(glyph_slot&& r):glyph_slot(std::exchange(r.handle, nullptr)){}
		~glyph_slot();

		void render(render_mode rm);

		ft::bitmap bitmap();
	/*public:
		inline bitmap& get_bitmap() { return bitmap_; }
		inline glyph_metrics& get_metrics() { return metrics; }

		inline int bitmap_left() { return handle->bitmap_left; }
		inline int bitmap_top() { return handle->bitmap_top; }
	};*/
	};
}