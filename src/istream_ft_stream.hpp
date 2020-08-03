#pragma once

#include "freetype/ftsystem.h"
#include <memory>
#include <istream>
#include <functional>

using namespace std;

namespace ft {

class istream_ft_stream : public FT_StreamRec_ {
    unique_ptr<istream> istream;

public:
    istream_ft_stream(unique_ptr<std::istream> is, void(*on_close)(istream_ft_stream*))
    :
    istream{move(is)}
    {
        istream->exceptions(ios::badbit | ios::failbit);
        base = nullptr;
        pos = istream->tellg();
        size = 0x7FFFFFFF;
        cursor=0;

        read = [](
            FT_Stream stream,
            u_long offset,
            u_char* buffer,
            u_long count
        ) -> u_long
        {
            auto& istream = ((istream_ft_stream*)stream)->istream;

            if(!count && offset > stream->size)
                return 1;

            if(stream->pos != offset) {
                istream->seekg(offset, std::ios_base::beg);
            }
            istream->read((char*)buffer, count);
            return istream->gcount();
        };

        close = (FT_Stream_CloseFunc)on_close;
    }
};

}
