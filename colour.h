#pragma once

#include "utils.h"

using Colour = Vec3;
using Color = Colour;

inline double linear_to_gamma(double linear)
{
    return (linear > 0) ? std::sqrt(linear) : 0;
}

void write_colour(std::ostream& out, const Colour& pixel_colour)
{
    auto r = pixel_colour[0];
    auto g = pixel_colour[1];
    auto b = pixel_colour[2];

    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    static const Interval intensity(0.000, 0.999);
    
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}