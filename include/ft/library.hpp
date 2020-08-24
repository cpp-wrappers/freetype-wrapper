#pragma once

#include <vector>
#include <memory>
#include <istream>
#include <set>

#include "face.hpp"

namespace ft {

	class face;

	class library {
		void* handle;

	public:
		library();
		library(library&& r):handle{std::exchange(r.handle, nullptr)}{}
		~library();

		template<class IStream>
		std::enable_if_t<std::is_base_of_v<std::istream, IStream>, face>
		face_from_istream(IStream istream) {
			return face_from_istream(std::make_unique<IStream>(std::move(istream)));
		}

		face face_from_istream(std::unique_ptr<std::istream> istream);
	};
}