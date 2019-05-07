#include "freetype/ftsystem.h"
#include <memory>

namespace freetype {

template<class IStream>
class std_cpp_ft_stream : public FT_StreamRec_ {
    IStream istream;

public:
    std_cpp_ft_stream(IStream&& istream)
    :
    istream{std::forward(istream)}
    {
        base = nullptr;
        size = 0x7FFFFFFF;
        pos = istream.tellg();

        read = [](
            FT_Stream stream,
            u_long offset,
            u_char* buffer,
            u_long count
        ) -> u_long
        {
            auto istream = ((std_ft_stream*)stream)->istream; 
            istream.seekg(offset, std::ios::beg);
            if(count == 0)
                return 0;
            istream.read((char*)buffer, count);
            return istream.gcount();
        };

        //close = [](FT_Stream  stream) {
        //    ((std_ft_stream*)stream)->istream.release();
        //};
    }
};

}
