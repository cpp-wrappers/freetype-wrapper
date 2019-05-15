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
#include "render_mode.hpp"

namespace freetype {
	using glyph_index = uint;

	class glyph_slot;

	class face {
		friend class library;

		FT_Face handle;
		glyph_slot glyph_slot_;
		size size_;

		face(FT_Face handle)
		:
		handle{ handle },
		glyph_slot_{handle->glyph},
		size_{handle->size}
		{
			handle->generic.data = this;
			handle->generic.finalizer = [](void* data) {
				(*(face*)data).~face();
			};
		}
	public:
		face(face&& r)
		:
		glyph_slot_{std::move(r.glyph_slot_)},
		size_{std::move(r.size_)}
		{
			handle = std::exchange(r.handle, nullptr);
			handle->generic.data = this;
		}

		face& operator=(face&& f) {
			glyph_slot_ = std::move(f.glyph_slot_);
			size_ = std::move(f.size_);
			handle = std::exchange(f.handle, nullptr);
			handle->generic.data = this;
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

		inline void load_and_render_glyph(glyph_index index, render_mode rm) {
			internal::check_for_error (
				FT_Load_Glyph(handle, index, FT_LOAD_RENDER | FT_LOAD_TARGET_((uint)rm))
			);
			
			glyph_slot_.handle = handle->glyph;
		}

		inline glyph_slot& glyph() {
			return glyph_slot_;
		}

		inline unsigned short units_per_em() {
			return handle->units_per_EM;
		}

		inline size& get_size() {
			return size_;
		}

		inline const std::string style_name() {
			return handle->style_name;
		}
	};
}
