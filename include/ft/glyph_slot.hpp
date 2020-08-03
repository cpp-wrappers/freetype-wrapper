#pragma once

#include <utility>
#include <memory>

namespace ft {
	class glyph_slot {
		friend class library;
		void* handle;
		
		glyph_slot(void* handle);

	/*public:
		inline bitmap& get_bitmap() { return bitmap_; }
		inline glyph_metrics& get_metrics() { return metrics; }

		inline int bitmap_left() { return handle->bitmap_left; }
		inline int bitmap_top() { return handle->bitmap_top; }
	};*/
	};
}