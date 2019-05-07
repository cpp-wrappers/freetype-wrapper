#pragma once

#include "freetype_fwd.hpp"
#include FT_SIZES_H
#include "internal/error.hpp"
#include <utility>

namespace freetype {

class size {
    friend class face;
    FT_Size handle;

    size(FT_Size handle):handle{handle} {
        handle->generic.data = this;
        handle->generic.finalizer = [](void* p){delete (size*)p;};
    }

public:
    size(size&& r) {
        handle = std::exchange(r.handle, nullptr);
        handle->generic.data = this;
    }

    ~size() {
        if(handle) internal::check_for_error(
            FT_Done_Size(std::exchange(handle, nullptr))
        );
    }

    using size_metrics = FT_Size_Metrics;

    size_metrics get_size_metrics() { return handle->metrics; }
};

}