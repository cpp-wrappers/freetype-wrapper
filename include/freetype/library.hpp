#pragma once

#include "freetype_fwd.hpp"
#include "face.hpp"
#include <vector>
#include <memory>
#include "internal/istream_wrapper.hpp"
#include "internal/error.hpp"

namespace freetype {

	class library {
		FT_Library handle;

	public:
		library() {
			internal::check_for_error(FT_Init_FreeType(&handle));
		}

		~library() {
			if(handle)
				internal::check_for_error(FT_Done_FreeType(std::exchange(handle, nullptr)));
		}

		template<class IStream>
		face face_from_istream(IStream&& istream) const {
			FT_Face face_handle;
			FT_Open_Args args;
			args.flags = FT_OPEN_STREAM;
			args.stream = new std_cpp_ft_stream(std::forward(istream));

			internal::check_for_error(FT_Open_Face(handle, &args, 0, &face_handle));
			face face_wrapper(face_handle);

			using generic_data_t = std::pair<face*, std_cpp_ft_stream*>;

			face_handle->generic.data = new generic_data_t(
				&face_wrapper,
				(std_cpp_ft_stream*) args.stream
			);

			face_handle->generic.finalizer = [](void* v) {
				auto pair = (generic_data_t*)v;

				if(pair->first->handle)
					delete pair->first;
				
				delete pair->second;
				delete pair;
			};

			return face;
		}
	};
}