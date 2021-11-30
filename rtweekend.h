#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = acos(-1);

inline double degrees_to_radians(double degrees) { return degrees * pi / 180; }

#include "ray.h"
#include "vec3.h"

#endif