#ifndef MATH_TUPLE_H
#define MATH_TUPLE_H


namespace math{
    template<int SIZE, typename T>
    class Tuple{
    protected:
        // array to hold the values
        T data[SIZE];
    public:
        // default constructor
        Tuple(){
            for(int i = 0; i < SIZE; i++){
                data[i] = 0;
            }
        }
        // initialize list constructor
         Tuple(std::initializer_list<T> init) {
                int i = 0;
                for (typename std::initializer_list<T>::const_iterator it = init.begin(); it != init.end() && i < SIZE; ++it) {
                    data[i++] = *it; // Assign value to array
                }
                for (; i < SIZE; ++i) {
                    data[i] = T(0); // Fill remaining elements with 0
                }
            }
        // Access element (non-const)
            T& operator[](int index) {
                return data[index];
            }

            // Access element (const version)
            const T& operator[](int index) const {
                return data[index];
            }
    };
} // namespace math

#endif // MATH_VEC3_H