#pragma once

#include <iostream>
#include "vec3.h"

using Colour = Vec3;
using Color = Colour;

void write_colour(std::ostream& out, const Colour& pixel_colour)
{
    auto r = pixel_colour[0];
    auto g = pixel_colour[1];
    auto b = pixel_colour[2];

    int rbyte = int(255.99 * r);
    int gbyte = int(255.99 * g);
    int bbyte = int(255.99 * b);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}