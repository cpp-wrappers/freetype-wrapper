#pragma once

#include "freetype_fwd.hpp"
#include "internal/error.hpp"
#include "glyph_slot.hpp"
#include "bbox.hpp"
#include "size_metrics.hpp"
#include "size.hpp"
#include <memory>
#include <functional>
#include <string>

namespace freetype {
	typedef unsigned glyph_index;

	class glyph_slot;

	class face {
		friend class library;

		FT_Face handle;
		glyph_slot glyph;
		size* size_ptr;

		face(FT_Face handle)
		:handle{ handle } {
			size_ptr = 
		}
	public:
		face(face&& r) {
			handle = std::exchange(r.handle, nullptr);
		}

		face& operator=(face&& f) {
			handle = std::exchange(f.handle, nullptr);
			return *this;
		}

		inline ~face() {
			if(handle) {
				internal::check_for_error(FT_Done_Face(std::exchange(handle, nullptr)));
			}
		}

		inline glyph_index get_char_index(unsigned charcode) {
			return FT_Get_Char_Index(handle, charcode);
		}

		inline void set_char_size(int w, int h, int hr, int vr) {
			internal::check_for_error(
				FT_Set_Char_Size(handle, w, h, hr, vr)
			);
		}

		inline bbox get_bbox() {
			return handle->bbox;
		}

		inline void load_glyph(glyph_index index) {
			internal::check_for_error (
				FT_Load_Glyph(handle, index, FT_LOAD_RENDER)
			);

			
			glyph.handle = handle->glyph;

			//handle->glyph->generic.data = new glyph_slot(handle->glyph);
			//handle->glyph->generic.finalizer = [](void* g){ delete (glyph_slot*)g; };
		}

		inline glyph_slot& glyph() {
			return glyph;
		}

		inline unsigned short units_per_em() {
			return handle->units_per_EM;
		}

		inline size& get_size() {
			return *size_ptr;
		}

		inline const std::string style_name() {
			return handle->style_name;
		}
	};
}
