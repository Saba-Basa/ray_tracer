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
    using reference = T&;
    using const_reference = const T&;

    // Inherit constructors and data member
    using math::Vec3<T>::Vec3;
    using math::Vec3<T>::data;
    using math::Vec3<T>::operator=;

    // Constructors
    Color() : math::Vec3<T>() {}
    Color(T r, T g, T b) : math::Vec3<T>(r, g, b) {}

    // Accessors methods
    reference r() { return data[0]; }
    reference g() { return data[1]; }
    reference b() { return data[2]; }

    const_reference r() const { return data[0]; }
    const_reference g() const { return data[1]; }
    const_reference b() const { return data[2]; }

    // Convert color to byte
    uint8_t toByte(T v) const {
        T clamped = std::max(T(0), std::min(T(1), v));
        return static_cast<uint8_t>(clamped * T(255));
    }

    // Operator overloads
    Color& operator+=(const Color& rhs) {
        data[0] += rhs.data[0];
        data[1] += rhs.data[1];
        data[2] += rhs.data[2];
        return *this;
    }

    Color& operator*=(T a) {
        data[0] *= a;
        data[1] *= a;
        data[2] *= a;
        return *this;
    }

    Color operator*(T a) const {
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
template<typename T>
Color<T> operator*(T a, const Color<T>& c) {
    return c * a;
}

} // namespace rt

#endif