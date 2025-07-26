#pragma once

#include "hittable.h"

class Material
{
    public:
        virtual ~Material() = default;

        virtual bool scatter(const Ray& r, const HitRecord& rec, Colour& attenuation, Ray& scattered) const
        {
            return false; 
        }
};

class Lambertian : public Material
{
    public:
        Lambertian(const Colour& albedo) : albedo(albedo) {}

        bool scatter(const Ray& r, const HitRecord& rec, Colour& attenuation, Ray& scattered) const override
        {
            Vec3 scatter_direction = rec.normal + random_unit_vector();

            if (scatter_direction.near_zero())
            {
                scatter_direction = rec.normal;    
            }
            
            scattered = Ray(rec.p, scatter_direction);
            attenuation = albedo;
            return true;
        }

    private:
        Colour albedo;
};

class Metal : public Material
{
    public:
        Metal(const Colour& albedo) : albedo(albedo) {}

        bool scatter(const Ray& r, const HitRecord& rec, Colour& attenuation, Ray& scattered) const override
        {
            Vec3 reflected = reflect(r.direction(), rec.normal);
            scattered = Ray(rec.p, reflected);
            attenuation = albedo;
            return true;
        }

    private:
        Colour albedo;
};