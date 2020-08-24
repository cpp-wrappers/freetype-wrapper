#pragma once

#include <string_view>
#include <utility>
#include "types.hpp"
#include "glyph_slot.hpp"

namespace ft {
	class face {
		friend class library;

		void* handle;

		face(void* handle);
	public:
		~face();
		face(face&& r) : face(std::exchange(r.handle, nullptr)) {};

		std::string_view family_name();
		std::string_view style_name();

		void char_size(fp26_6_t w, fp26_6_t h, unsigned hor, unsigned vert);

		unsigned char_index(unsigned long charcode);

		void load_glyph(unsigned ci);

		ft::glyph_slot& glyph();
	};
}
