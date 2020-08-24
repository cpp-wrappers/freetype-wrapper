#include "../include/ft/face.hpp"
#include "freetype_fwd.hpp"
#include <utility>
#include "error.hpp"

using namespace ft;
using namespace std;

inline FT_Face f(void* p) { return (FT_Face) p; }

face::face(void* p)
:handle{p} {
    f(p)->generic.data = this;
    f(p)->generic.finalizer = [](void* p) {
        ((face*)p)->~face();
    };
    glyph_slot::wrap(f(p)->glyph);
}

face::~face() { if(handle) FT_Done_Face(f(exchange(handle, nullptr))); }

string_view face::family_name() {
    FT_String* name = f(handle)->family_name;
    return name not_eq nullptr ? string_view{name} : string_view{};
}

string_view face::style_name() {
    FT_String* name = f(handle)->family_name;
    return name not_eq nullptr ? string_view{name} : string_view{};
}

void face::char_size(fp26_6_t w, fp26_6_t h, unsigned hor, unsigned vert) {
    check_for_error(
        FT_Set_Char_Size(f(handle), w, h, hor, vert)
    );
}

unsigned face::char_index(unsigned long charcode) {
    return FT_Get_Char_Index(f(handle), charcode);
}

void face::load_glyph(unsigned ci) {
    check_for_error(
        FT_Load_Glyph(f(handle), ci, FT_LOAD_DEFAULT)
    );
}

ft::glyph_slot& face::glyph() {
    return * ( (ft::glyph_slot*) f(handle)->glyph->generic.data );
}
