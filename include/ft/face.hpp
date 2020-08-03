#pragma once

#include <string_view>
#include "types.hpp"

namespace ft {
	class face {
		friend class library;

		void* handle;

		face(void* handle);
	public:
		~face();

		std::string_view family_name();
		std::string_view style_name();

		void set_char_size(fp26_6_t w, fp26_6_t h, unsigned hor, unsigned vert);
	};
}
