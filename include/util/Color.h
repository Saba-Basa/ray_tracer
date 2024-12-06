#ifndef UTIL_COLOR_H
#define UTIL_COLOR_H

#include "rt.h"
#include "math/Vec3.h"

namespace rt {

template<typename T>
class Color : public math::Vec3<T> {
public:
    using typename math::Vec3<T>::value_type;
    using typename math::Vec3<T>::reference;
    using typename math::Vec3<T>::const_reference;

    Color() : math::Vec3<T>() {}
    Color(T r, T g, T b) : math::Vec3<T>(r, g, b) {}

    reference r() { return this->x(); }
    reference g() { return this->y(); }
    reference b() { return this->z(); }

    const_reference r() const { return this->x(); }
    const_reference g() const { return this->y(); }
    const_reference b() const { return this->z(); }

    uint8_t toByte(T v) const { return static_cast<uint8_t>(v * T(255)); }
};

} // namespace rt

#endif
