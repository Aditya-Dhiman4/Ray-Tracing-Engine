#pragma once

#include "utils.h"

class Vec3
{
    public:
        double val[3];

        // constructors
        constexpr Vec3() : val{0, 0, 0} {}
        constexpr Vec3(double x, double y, double z) : val{x, y, z} {}

        // getters
        constexpr double x() const { 
            return val[0]; 
        }

        constexpr double y() const { 
            return val[1]; 
        }

        double z() const { 
            return val[2]; 
        }


        // operations
        constexpr Vec3 operator-() const
        {
            return Vec3(-val[0], -val[1], -val[2]);
        }

        constexpr double operator[](int i) const
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

        constexpr double length_squared() const
        {
            return (val[0] * val[0]) + (val[1] * val[1]) + (val[2] * val[2]);
        }

        bool near_zero() const
        {
            double s = 1e-8;
            return (std::fabs(val[0]) < s) && (std::fabs(val[1]) < s) && (std::fabs(val[2]) < s);
        }

        static Vec3 random()
        {
            return Vec3(random_double(), random_double(), random_double());
        }

        static Vec3 random(double min, double max)
        {
            return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }
};

using Point3 = Vec3;

inline std::ostream& operator<<(std::ostream& out, const Vec3& v)
{
    return out << v.val[0] << v.val[1] << v.val[2];
}

// element wise vector operations
constexpr Vec3 operator+(const Vec3& u, const Vec3& v)
{
    return Vec3(u.val[0] + v.val[0], u.val[1] + v.val[1], u.val[2] + v.val[2]);
}

constexpr Vec3 operator-(const Vec3& u, const Vec3& v)
{
    return Vec3(u.val[0] - v.val[0], u.val[1] - v.val[1], u.val[2] - v.val[2]);
}

constexpr Vec3 operator*(const Vec3& u, const Vec3& v)
{
    return Vec3(u.val[0] * v.val[0], u.val[1] * v.val[1], u.val[2] * v.val[2]);
}

// scalar vector operations
constexpr Vec3 operator/(const Vec3& u, double v)
{
    return Vec3(u.val[0] / v, u.val[1] / v, u.val[2] / v);
}

constexpr Vec3 operator*(double u, const Vec3& v)
{
    return Vec3(u * v.val[0], u * v.val[1], u * v.val[2]);
}

constexpr Vec3 operator*(const Vec3& u, double v)
{
    return Vec3(u.val[0] * v, u.val[1] * v, u.val[2] * v);
}

constexpr double dot(const Vec3& u, const Vec3& v)
{
    return (u[0] * v[0]) + (u[1] * v[1]) + (u[2] * v[2]);
}

constexpr Vec3 cross(const Vec3& u, const Vec3& v)
{
    return Vec3(u.val[1] * v.val[2] - u.val[2] * v.val[1],
                u.val[2] * v.val[0] - u.val[0] * v.val[2],
                u.val[0] * v.val[1] - u.val[1] * v.val[0]);
}

inline Vec3 unit_vector(const Vec3& v)
{
    return v / v.length();
}

// Marsaglia's Disk to Sphere Projection
inline Vec3 random_unit_vector()
{   
    while(true)
    {
        double u = random_double(-1, 1);
        double v = random_double(-1, 1);
        double s = (u*u) + (v*v);

        if (1e-160 < s && s <= 1)
        {
            double t = 2 * std::sqrt(1 - s);
            return Vec3(u * t, v * t, 1 - 2 * s);
        }
    }
}

// Rejection Sampling
// inline Vec3 random_unit_vector()
// {   
//     while(true)
//     {
//         Vec3 p = Vec3::random(-1, 1);
//         double len_sq = p.length_squared();

//         if (1e-160 < len_sq && len_sq <= 1)
//         {
//             return p / sqrt(len_sq);
//         }
//     }
// }

inline Vec3 random_on_hemisphere(const Vec3& normal)
{
    Vec3 random_vec = random_unit_vector();
    if (dot(random_vec, normal) > 0.0)
    {
        return random_vec;
    }
    else
    {
        return -random_vec;
    }
}

constexpr Vec3 reflect(const Vec3& v, const Vec3& n)
{
    return v - (2 * dot(v, n) * n);
}

inline Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat) {
    auto cos_theta = std::fmin(dot(-uv, n), 1.0);
    Vec3 r_out_perp =  etai_over_etat * (uv + (cos_theta*n));
    Vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

inline Vec3 random_in_unit_disk()
{
    while(true)
    {
        auto p = Vec3(random_double(-1, 1), random_double(-1, 1), 0.0);
        if (p.length_squared() < 1.0)
        {
            return p;
        }
    }
}