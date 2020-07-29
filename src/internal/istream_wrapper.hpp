#pragma once

#include "freetype/ftsystem.h"
#include <memory>
#include <ios>
#include <functional>

namespace freetype {

class std_cpp_ft_stream : public FT_StreamRec_ {
    std::unique_ptr<std::istream> istream;

public:
    template<class IStream>
    std_cpp_ft_stream(IStream&& istream, void(*on_close)(std_cpp_ft_stream*))
    :
    istream{std::make_unique<IStream>(std::forward<IStream>(istream))}
    {
        istream.exceptions(std::ios::badbit | std::ios::failbit);
        base = nullptr;
        pos = istream.tellg();
        size = 0x7FFFFFFF;
        cursor=0;

        read = [](
            FT_Stream stream,
            u_long offset,
            u_char* buffer,
            u_long count
        ) -> u_long
        {
            auto& istream = ((std_cpp_ft_stream*)stream)->istream;

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
