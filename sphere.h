#pragma once

#include "hittable.h"

class Sphere : public Hittable
{
    public:
        Sphere(const Point3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}

        bool hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const override
        {
            Vec3 dist = center - r.origin();

            /**
             * Formula for calculating ray/sphere intersection point
             * is a modified quadratic formula
             * 
             * t = (h +- sqrt(h^2 - ac)) / a
             * 
             * where:
             * h = b / (-2)
             * a = d * d
             * b = -2d * (C - Q)
             * c = (C - Q) * (C - Q) - r^2
             * 
             * d = direction of the ray
             * C = center of the sphere
             * Q = origin of the ray
             */

            double a = dot(r.direction(), r.direction());
            double h = dot(r.direction(), dist);
            double c = dot(dist, dist) - (radius * radius);
            double discriminant = (h*h) - (a*c);

            if (discriminant < 0)
            {
                return false;
            }

            double discriminantSqrt = std::sqrt(discriminant);

            double root = (h - discriminantSqrt) / a;
            if (root <= ray_tmin || root >= ray_tmax)
            {
                double root = (h + discriminantSqrt) / a;
                if (root <= ray_tmin || root >= ray_tmax)
                {
                    return false;
                }
            }

            rec.t = root;
            rec.p = r.at(root);
            Vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);

            return true;
        }

    private:
        Point3 center;
        double radius;
};