#pragma once

#include <thread>
#include <atomic>
#include "immintrin.h"

#include "constants.h"

#include "hittable_list.h"
#include "material.h"

class Camera
{
    public:
        double aspect_ratio = 16.0 / 9.0;    
        int image_width = 1920;
        int samples_per_pixel = 10;
        int max_depth = 10;
        int thread_granularity = 1;

        void render(const HittableList& objects)
        {
            initialize();

            const int num_threads = std::thread::hardware_concurrency();
            std::vector<std::thread> thread_list;

            std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

            for (int i = 0; i < num_threads; i++)
            {
                thread_list.emplace_back(
                    &Camera::render_rows,
                    this,
                    std::cref(objects)
                );
            }

            for (auto& thread : thread_list)
            {
                if (thread.joinable()) thread.join();
            }

            for (auto& pixel : image) {
                write_colour(std::cout, pixel);
            }
        }

    private:
        int image_height;
        Point3 pixel_ul_pos;
        Vec3 delta_u;
        Vec3 delta_v;
        Point3 camera_center;
        double pixel_sample_scale;
        std::vector<Colour> image;
        std::atomic<int> row_count;

        void initialize()
        {
            image_height = int(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            image.assign(image_width * image_height, Colour{0,0,0});

            // Camera
            double focal_length = 1.0;
            double viewport_height = 2.0;
            double viewport_width = viewport_height * (double(image_width)/image_height);
            camera_center = Point3(0, 0, 0);

            // Camera Vectors
            Vec3 viewport_u = Vec3(viewport_width, 0, 0);
            Vec3 viewport_v = Vec3(0, -viewport_height, 0);

            // Camera Delta Vectors
            delta_u = viewport_u / image_width;
            delta_v = viewport_v / image_height;

            // Render
            Vec3 viewport_upper_left = camera_center - Vec3(0, 0, focal_length) - (viewport_u / 2) - (viewport_v / 2);
            pixel_ul_pos = viewport_upper_left + 0.5 * (delta_u + delta_v);

            pixel_sample_scale = 1.0 / samples_per_pixel;

            // initialize atomic count
            row_count = 0;
            
        }

        void render_rows(const HittableList& objects)
        {

            for(;;)
            {
                int row = row_count.fetch_add(1);
                
                // Exit if no rows left to render
                if (row >= image_height) return;

                int row_start = row;
                int row_end = std::min(row + thread_granularity, image_height);
                
                for (int j = row_start; j < row_end; j++) 
                {
                    // std::clog << "\rScanlines remaining: " << (num_rows - j) << ' ' << std::flush;
                    for (int i = 0; i < image_width; i++) 
                    {
                        Colour pixel_colour(0,0,0);

                        for (int sample = 0; sample < samples_per_pixel; sample++)
                        {
                            Ray r = get_ray(i, j);
                            pixel_colour += ray_colour(r, max_depth, objects);
                        }

                        // write the pixel to the image
                        image[(j * image_width) + i] = pixel_colour * pixel_sample_scale;
                    }
                }
            }
            // std::clog << "\rDone.                 \n";
        }
    
        Ray get_ray(int i, int j)
        {
            Vec3 offset = sample_square();
            Vec3 pixel_sample = pixel_ul_pos + ((i + offset.x()) * delta_u) + ((j + offset.y()) * delta_v);

            Point3 ray_origin = camera_center;
            Vec3 ray_direction = pixel_sample - ray_origin;

            return Ray(ray_origin, ray_direction);
        }

        Vec3 sample_square()
        {
            return Vec3(random_double() -0.5, random_double() -0.5, 0);
        }
    
        Colour ray_colour(const Ray& r, int depth, const HittableList& objects)
        {
            if (depth <= 0)
            {
                return Colour(0,0,0);
            }
            
            HitRecord rec;
            if (objects.hit(r, Interval(0.001, infinity), rec))
            {
                Ray scattered;
                Colour attenuation;
                
                if (rec.mat->scatter(r, rec, attenuation, scattered))
                {
                    return attenuation * ray_colour(scattered, depth - 1, objects);
                }

                return Colour(0,0,0);
            }
            
            Vec3 unit_direction = unit_vector(r.direction());
            double a = 0.5 * (unit_direction.y() + 1.0);
            return (1.0 - a) * Colour(1.0, 1.0, 1.0) + a * Colour(0.5, 0.7, 1.0);
        }

};