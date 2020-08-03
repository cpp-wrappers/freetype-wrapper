#include "../include/ft/library.hpp"

#include "freetype_fwd.hpp"
#include "error.hpp"
#include "istream_ft_stream.hpp"
#include <utility>

using namespace ft;
using namespace std;

static inline FT_Library l(void* h) { return (FT_Library)h; }

library::library() {
    check_for_error(
        FT_Init_FreeType((FT_Library*)&handle)
    );
}

library::~library() {
    if(handle)
        check_for_error(
            FT_Done_FreeType(l(exchange(handle, nullptr)))
        );
}

face library::face_from_istream(unique_ptr<istream> is) {
    FT_Face face_handle;
    FT_Open_Args args;
    args.flags = FT_OPEN_STREAM;
    args.stream = new istream_ft_stream{
        std::move(is),
        [](istream_ft_stream* str) { delete str; }
    };

    check_for_error(
        FT_Open_Face(l(handle), &args, 0, &face_handle)
    );

    return {face_handle};
}