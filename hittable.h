#pragma once

#include "ray.h"

class Material;

class HitRecord
{
    public:
        Point3 p;
        Vec3 normal;
        shared_ptr<Material> mat;
        double t;
        bool front_face;

        void set_face_normal(const Ray& r, const Vec3& outward_normal)
        {
            front_face = (dot(r.direction(), outward_normal) < 0.0);
            normal = (front_face) ? outward_normal : -outward_normal;
        }
};

class Hittable
{
    public:
        virtual ~Hittable() = default;
        virtual bool hit(const Ray& r, Interval t, HitRecord& rec) const = 0;
};