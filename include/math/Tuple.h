#ifndef MATH_TUPLE_H
#define MATH_TUPLE_H

//Base template for fixed-size arrays

/*
 - Provides common operations for vectors/points
*/

namespace math{

    //generic fixed-size array container
    template<int SIZE, typename T>
    class Tuple{

    public:
        // STL type definitions
        using value_type = T; // type of the elements stored in the container
        using size_type = std::size_t; // type for sizes and indices, handle container's max size
        using reference = T&; // type for modifiable element access, allows changing values
        using const_reference = const T&; // type for read-only element access, prevents modifications
        using iterator = T*; // pointer type for traversing / modifying elements, used in range-based operations

        // default constructor
        Tuple() : data() {}; // initialize all elements to 0


        // initialize list constructor
        Tuple(std::initializer_list<T> init) {
             size_type i = 0;
             for (const auto& value : init) {
                 if (i >= SIZE) break;
                 data[i++] = value;
             }
             // Fill remaining elements with zero
             for (; i < SIZE; ++i) {
                 data[i] = value_type{};
             }
         }


        reference operator[](size_type index) {
         return data[index];
        }

        const_reference operator[](size_type index) const {
         return data[index];
        }


        // access element (non-const)
        reference at(size_type index) {
                if (index >= SIZE) {
                    throw std::out_of_range("Index out of range");
                }
                return data[index];
            }

        // access element (const version)
        const_reference at(size_type index) const {
            if (index >= SIZE) {
                throw std::out_of_range("Index out of range");
            }
            return data[index];
        }

        protected:
            // storage array
            value_type data[SIZE];

    };
} // namespace math

#endif // MATH_VEC3_H