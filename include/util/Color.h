#ifndef UTIL_COLOR_H
#define UTIL_COLOR_H

#include "rt.h"
#include "math/Vec3.h"
#include <cstdint>
#include <cmath>

namespace rt {

template<typename T>
class Color : public math::Vec3<T> {
public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;

    // Inherit constructors and data member
    using math::Vec3<value_type>::Vec3;
    using math::Vec3<value_type>::data;
    using math::Vec3<value_type>::operator=;

    // Constructors
    Color() : math::Vec3<value_type>() {}
    Color(value_type r, value_type g, value_type b) : math::Vec3<value_type>(r, g, b) {}

    // Accessors methods
    reference r() { return data[0]; }
    reference g() { return data[1]; }
    reference b() { return data[2]; }

    const_reference r() const { return data[0]; }
    const_reference g() const { return data[1]; }
    const_reference b() const { return data[2]; }

    // Convert color to byte
    uint8_t toByte(value_type v) const {
        value_type clamped = std::max(T(0), std::min(value_type(1), v));
        return static_cast<uint8_t>(clamped * value_type(255));
    }

    // Operator overloads
    Color& operator+=(const Color& rhs) {
        data[0] += rhs.data[0];
        data[1] += rhs.data[1];
        data[2] += rhs.data[2];
        return *this;
    }

    Color& operator*=(value_type a) {
        data[0] *= a;
        data[1] *= a;
        data[2] *= a;
        return *this;
    }

    Color operator*(value_type a) const {
        Color result(*this);
        result *= a;
        return result;
    }

    Color operator+(const Color& rhs) const {
        Color result(*this);
        result += rhs;
        return result;
    }
};

// Non-member operator overloads
template<typename value_type>
Color<value_type> operator*(value_type a, const Color<value_type>& c) {
    return c * a;
}

} // namespace rt

#endif