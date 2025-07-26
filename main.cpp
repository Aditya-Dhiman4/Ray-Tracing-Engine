#include "constants.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"

int main() {
    // Objects
    HittableList objects;

    auto material_ground = make_shared<Lambertian>(Colour(0.8, 0.8, 0.0));
    auto material_center = make_shared<Lambertian>(Colour(0.1, 0.2, 0.5));
    auto material_left = make_shared<Metal>(Colour(0.8, 0.8, 0.8), 0.0);
    auto material_right  = make_shared<Metal>(Colour(0.8, 0.6, 0.2), 0.0);

    objects.add(make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    objects.add(make_shared<Sphere>(Point3( 0.0,    0.0, -1.2),   0.5, material_center));
    objects.add(make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.5, material_left));
    objects.add(make_shared<Sphere>(Point3( 1.0,    0.0, -1.0),   0.5, material_right));

    Camera camera;
    camera.samples_per_pixel = 100;
    camera.image_width = 1920;
    camera.max_depth = 25;

    camera.render(objects);
}