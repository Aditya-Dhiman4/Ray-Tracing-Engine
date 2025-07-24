#pragma once

#include <memory>
#include <limits>
#include <cmath>
#include <iostream>
#include <stdint.h>

using std::make_shared;
using std::shared_ptr;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double deg_to_rad(double deg)
{
    return deg * pi / 180.0;
}

#include "vec3.h"
#include "colour.h"
#include "ray.h"