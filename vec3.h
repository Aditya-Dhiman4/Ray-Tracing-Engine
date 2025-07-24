#pragma once

#include "constants.h"

class Vec3
{
    public:
        double val[3];

        // constructors
        Vec3() : val{0, 0, 0} {}
        Vec3(double x, double y, double z) : val{x, y, z} {}

        // getters
        double x() const { 
            return val[0]; 
        }

        double y() const { 
            return val[1]; 
        }

        double z() const { 
            return val[2]; 
        }


        // operations
        Vec3 operator-() const
        {
            return Vec3(-val[0], -val[1], -val[2]);
        }

        double operator[](int i) const
        {
            return val[i];
        }

        double& operator[](int i)
        {
            return val[i];
        }

        Vec3& operator+=(const Vec3& v)
        {
            val[0] += v.val[0];
            val[1] += v.val[1];
            val[2] += v.val[2];
            return *this;
        }

        Vec3& operator-=(const Vec3& v)
        {
            val[0] -= v.val[0];
            val[1] -= v.val[1];
            val[2] -= v.val[2];
            return *this;
        }

        Vec3& operator*=(const Vec3& v)
        {
            val[0] *= v.val[0];
            val[1] *= v.val[1];
            val[2] *= v.val[2];
            return *this;
        }

        Vec3& operator/=(const Vec3& v)
        {
            val[0] /= v.val[0];
            val[1] /= v.val[1];
            val[2] /= v.val[2];
            return *this;
        }

        double length() const
        {
            return std::sqrt(length_squared());
        }

        double length_squared() const
        {
            return (val[0] * val[0]) + (val[1] * val[1]) + (val[2] * val[2]);
        }
};

using Point3 = Vec3;

inline std::ostream& operator<<(std::ostream& out, const Vec3& v)
{
    return out << v.val[0] << v.val[1] << v.val[2];
}

// element wise vector operations
inline Vec3 operator+(const Vec3& u, const Vec3& v)
{
    return Vec3(u.val[0] + v.val[0], u.val[1] + v.val[1], u.val[2] + v.val[2]);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v)
{
    return Vec3(u.val[0] - v.val[0], u.val[1] - v.val[1], u.val[2] - v.val[2]);
}

inline Vec3 operator*(const Vec3& u, const Vec3& v)
{
    return Vec3(u.val[0] * v.val[0], u.val[1] * v.val[1], u.val[2] * v.val[2]);
}

// scalar vector operations
inline Vec3 operator/(const Vec3& u, double v)
{
    return Vec3(u.val[0] / v, u.val[1] / v, u.val[2] / v);
}

inline Vec3 operator*(double u, const Vec3& v)
{
    return Vec3(u * v.val[0], u * v.val[1], u * v.val[2]);
}

inline Vec3 operator*(const Vec3& u, double v)
{
    return Vec3(u.val[0] * v, u.val[1] * v, u.val[2] * v);
}

inline double dot(const Vec3& u, const Vec3& v)
{
    return (u[0] * v[0]) + (u[1] * v[1]) + (u[2] * v[2]);
}

inline Vec3 cross(const Vec3& u, const Vec3& v)
{
    return Vec3(u.val[1] * v.val[2] - u.val[2] * v.val[1],
                u.val[2] * v.val[0] - u.val[0] * v.val[2],
                u.val[0] * v.val[1] - u.val[1] * v.val[0]);
}

inline Vec3 unit_vector(const Vec3& v)
{
    return v / v.length();
}