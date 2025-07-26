#pragma once

#include <memory>
#include <limits>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <cstdint>

using std::make_shared;
using std::shared_ptr;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double deg_to_rad(double deg)
{
    return deg * pi / 180.0;
}

inline double random_double()
{
    return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max)
{
    return ((max - min) * random_double()) + min;
}

#include "interval.h"
#include "vec3.h"
#include "colour.h"
#include "ray.h"