#pragma once

#include <iostream>
#include <cmath>

class Vec3
{
    public:
        float val[3];

        // constructors
        Vec3() : val{0, 0, 0} {}
        Vec3(float x, float y, float z) : val{x, y, z} {}

        // getters
        float x() const { 
            return val[0]; 
        }

        float y() const { 
            return val[1]; 
        }

        float z() const { 
            return val[2]; 
        }


        // operations
        Vec3 operator-() const
        {
            return Vec3(-val[0], -val[1], -val[2]);
        }

        float operator[](int i) const
        {
            return val[i];
        }

        float& operator[](int i)
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

        float length() const
        {
            return std::sqrt(length_squared());
        }

        float length_squared() const
        {
            return (val[0] * val[0]) + (val[1] * val[1]) + (val[2] * val[2]);
        }
};

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
inline Vec3 operator/(const Vec3& u, float v)
{
    return Vec3(u.val[0] / v, u.val[1] / v, u.val[2] / v);
}

inline Vec3 operator*(float u, const Vec3& v)
{
    return Vec3(u * v.val[0], u * v.val[1], u * v.val[2]);
}

inline Vec3 operator*(const Vec3& u, float v)
{
    return Vec3(u.val[0] * v, u.val[1] * v, u.val[2] * v);
}

inline float dot(const Vec3& u, const Vec3& v)
{
    return (u * v).length();
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