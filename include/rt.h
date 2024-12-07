#ifndef CORE_PBRT_H
#define CORE_PBRT_H

#include <cstdint>
#include <vector>
#include <memory>
#include <string>

//Core definitions and forward declarations
namespace rt {

// Core type definitions
using Float = float;
using FloatBits = uint32_t;

// Forward declarations
template <typename T> class Vector3;
template <typename T> class Color;
template <typename T> class Image;

} // namespace rt

#endif