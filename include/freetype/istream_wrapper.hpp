#include "freetype/ftsystem.h"
#include <memory>

namespace freetype {
    class std_ft_stream : public FT_StreamRec_ {
        std::unique_ptr<std::istream> stream;
    public:

        std_ft_stream(std::unique_ptr<std::istream> s)
        :
	stream{std::move(s)}
        {
            base = nullptr;
            size = 0x7FFFFFFF;
            pos = stream->tellg();

            read = [](
                FT_Stream       stream,
                unsigned long   offset,
                unsigned char*  buffer,
                unsigned long   count)
		-> unsigned long
            {
                auto s = ((std_ft_stream*)stream)->stream.get(); 
                s->seekg(offset, std::ios::beg);
                if(count == 0)
                    return 0;
                s->read((char*)buffer, count);
                return s->gcount();
            };

            close = [](FT_Stream  stream) {
                ((std_ft_stream*)stream)->stream.release(); 
            };
        }
    };
}
