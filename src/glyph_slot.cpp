#include "../include/ft/glyph_slot.hpp"
#include "freetype_fwd.hpp"
#include "freetype/internal/ftobjs.h"
#include "error.hpp"
#include <utility>

using namespace ft;
using namespace std;

static inline FT_GlyphSlot gs(void* h) { return (FT_GlyphSlot)h; }

void glyph_slot::wrap(void* h) {
    gs(h)->generic.data = new glyph_slot(h);
    gs(h)->generic.finalizer = [](void* p) {
        delete (glyph_slot*)p;
    };
}

glyph_slot::glyph_slot(void* handle)
:handle{handle} {}

glyph_slot::~glyph_slot() {
    if(handle) FT_Done_GlyphSlot(gs(exchange(handle, nullptr)));
}

ft::bitmap glyph_slot::bitmap() {
    return {& (gs(handle)->bitmap)};
}

void glyph_slot::render(render_mode rm) {
    check_for_error(
        FT_Render_Glyph(gs(handle), (FT_Render_Mode)rm)
    );
}