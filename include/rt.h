#ifndef CORE_PBRT_H
#define CORE_PBRT_H

#include <cstdint>
#include <vector>
#include <memory>
#include <string>

namespace rt {

// Core type definitions
using Float = float;
using FloatBits = uint32_t;

// Forward declarations
template <typename T> class Vector2;
template <typename T> class Vector3;
template <typename T> class Point2;
template <typename T> class Point3;
template <typename T> class Color;
template <typename T> class Image;

// Common types
using Vector3f = Vector3<Float>;
using Point3f = Point3<Float>;
using Colorf = Color<Float>;

} // namespace rt

#endif