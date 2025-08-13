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
        Metal(const Colour& albedo, double fuzz) : albedo(albedo), fuzz(fuzz) {}

        bool scatter(const Ray& r, const HitRecord& rec, Colour& attenuation, Ray& scattered) const override
        {
            Vec3 reflected = reflect(r.direction(), rec.normal);

            if (fuzz > 1e-2)
            {
                reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
            }
            scattered = Ray(rec.p, reflected);
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }

    private:
        Colour albedo;
        double fuzz;
};

class Dielectric : public Material {
  public:
    Dielectric(double refraction_index) : refraction_index(refraction_index) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, Colour& attenuation, Ray& scattered)
    const override {
        attenuation = Colour(1.0, 1.0, 1.0);
        double ri = rec.front_face ? (1.0/refraction_index) : refraction_index;

        Vec3 unit_direction = unit_vector(r_in.direction());

        double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = std::sqrt(1.0 - (cos_theta*cos_theta));

        Vec3 direction;
        bool reflect_ray = ri * sin_theta > 1.0;
        
        if (reflect_ray || reflectance(cos_theta, ri) > random_double())
        {
            direction = reflect(unit_direction, rec.normal);
        }
        else
        {
            direction = refract(unit_direction, rec.normal, ri);
        }

        scattered = Ray(rec.p, direction);
        return true;
    }

  private:
    double refraction_index;

    static double reflectance(double cosine, double refraction_index)
    {
        double r0 = (1 - refraction_index) / (1 + refraction_index);
        r0 = r0*r0;
        return r0 + (1 - r0) * std::pow(1 - cosine, 5);
    }
};