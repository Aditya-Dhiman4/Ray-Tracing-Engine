#include "constants.h"

#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

Colour ray_colour(const Ray& r, const HittableList& objects)
{
    HitRecord rec;
    if (objects.hit(r, 0, infinity, rec))
    {
        return 0.5 * (rec.normal + Colour(1, 1, 1));
    }
    
    Vec3 unit_direction = unit_vector(r.direction());
    double a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * Colour(1.0, 1.0, 1.0) + a * Colour(0.5, 0.7, 1.0);
}

int main() {

    // Image
    double aspect_ratio = 16.0 / 9.0;
    const uint16_t image_width = 1920;

    // Determine Image Height
    uint16_t image_height = uint16_t(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Objects
    HittableList objects;

    objects.add(make_shared<Sphere>(Point3(0,0,-1), 0.5));
    objects.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // Camera
    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * (double(image_width)/image_height);
    Point3 camera_center = Point3(0, 0, 0);

    // Camera Vectors
    Vec3 viewport_u = Vec3(viewport_width, 0, 0);
    Vec3 viewport_v = Vec3(0, -viewport_height, 0);

    // Camera Delta Vectors
    Vec3 delta_u = viewport_u / image_width;
    Vec3 delta_v = viewport_v / image_height;

    // Render
    Vec3 viewport_upper_left = camera_center - Vec3(0, 0, focal_length) - (viewport_u / 2) - (viewport_v / 2);
    Point3 pixel_ul_pos = viewport_upper_left + 0.5 * (delta_u + delta_v);

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            // create the ray
            Point3 pixel_center = pixel_ul_pos + (i * delta_u) + (j * delta_v);
            Vec3 ray_direction = pixel_center - camera_center;
            Ray r(camera_center, ray_direction);

            Colour pixel_colour = ray_colour(r, objects);

            // write the pixel to the image
            write_colour(std::cout, pixel_colour);
        }
    }

    std::clog << "\rDone.                 \n";
}