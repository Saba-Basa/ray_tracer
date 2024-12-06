#ifndef MATH_VEC3_H
#define MATH_VEC3_H

#include "math/Tuple.h"

namespace math{

template<typename T>
class Vec3: public Tuple<3, T>
{

public:
    // STL type definitions
    using value_type = T; // type of the elements stored in the container
    using reference = T&; // type for modifiable element access, allows changing values
    using const_reference = const T&; // type for read-only element access, prevents modifications

    // default constructor
    Vec3() : Tuple<3, value_type>() {}; // initialize all elements to 0

    // initialize a constructor with three arguments
    Vec3(value_type x, value_type y, value_type z) {
        this->data[0] = x;
        this->data[1] = y;
        this->data[2] = z;
    }

    Vec3(std::initializer_list<T> init) : Tuple<3, T>(init) {}

    // access element (non-const)
    reference x() {return this->data[0];} // access element (non-const)
    reference y() {return this->data[1];} // access element (non-const)
    reference z() {return this->data[2];} // access element (non-const)

    // access element (const version)
    const_reference x() const {return this->data[0];} // access element (const version)
    const_reference y() const {return this->data[1];} // access element (const version)
    const_reference z() const {return this->data[2];} // access element (const version)

};
} // namespace math

#endif // MATH_VEC3_H