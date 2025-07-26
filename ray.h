#pragma once

#include "vec3.h"

/**
 * A Ray is defined as the parametric form of a line:
 * 
 * P(t) = A + tb
 * 
 * Where A and b are vectors, and t is a scalar
 */

class Ray
{
    public:
        Ray() {}
    
        Ray(const Point3& origin, const Vec3& direction) : A(origin), b(direction) {}

        const Point3& origin() const
        {
            return A;
        }
        const Point3& direction() const
        {
            return b;
        }

        inline Point3 at(double t) const
        {
            return A + (t * b);
        }
    private:
        Point3 A;
        Vec3 b;
};