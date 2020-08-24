#pragma once

#include <cstdint>
#include <cmath>

namespace ft {

template<class T, unsigned integer_bits>
union fp_t {
    static constexpr unsigned fractional_bits = sizeof(T)*8-integer_bits;
    T 
        integer : integer_bits,
        fractional : fractional_bits;
    T val;

    explicit fp_t(T i, T f) {
        integer = i;
        fractional = f;
    }
    explicit fp_t(float v) {
        integer = v;
        fractional = (v-integer) * std::exp2(fractional_bits);
    }
    operator T() {return val;}
};

using fp26_6_t = fp_t<uint32_t, 26>;

}