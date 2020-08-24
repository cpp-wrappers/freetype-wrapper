#include "../include/ft/bitmap.hpp"
#include "freetype_fwd.hpp"

unsigned char* ft::bitmap::_data() {
    return ((FT_Bitmap*)handle)->buffer;
}

unsigned ft::bitmap::rows() { return ((FT_Bitmap*)handle)->rows; }
unsigned ft::bitmap::width() { return ((FT_Bitmap*)handle)->width; }
unsigned ft::bitmap::pitch() { return ((FT_Bitmap*)handle)->pitch; }
unsigned ft::bitmap::num_grays() { return ((FT_Bitmap*)handle)->num_grays; }