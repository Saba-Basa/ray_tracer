#ifndef MATH_POINT_H
#define MATH_POINT_H

#include "math/Tuple.h"
#include "math/Vec3.h"


namespace math{

template<typename T>
class Point: public Tuple<3, T>
{
public:
    // STL type definitions
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;

    //Default Contructor
    Point() : Tuple<3, value_type>() {}; // initialize all elements to 0
    //Constructor with Coordinates
    Point(value_type x, value_type y, value_type z) {
        this->data[0] = x;
        this->data[1] = y;
        this->data[2] = z;
    }
    // Accessors
    reference x() {return this->data[0];}
    reference y() {return this->data[1];}
    reference z() {return this->data[2];}

    const_reference x() const {return this->data[0];}
    const_reference y() const {return this->data[1];}
    const_reference z() const {return this->data[2];}
};
} // namespace math

#endif // MATH_POINT_H