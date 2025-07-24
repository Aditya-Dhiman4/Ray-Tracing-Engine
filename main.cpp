#include <iostream>
#include <stdint.h>

#include "vec3.h"
#include "colour.h"

int main() {

    // Image

    const uint16_t image_width = 256;
    const uint16_t image_height = 256;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            // create the pixel
            auto pixel_colour = colour(
                float(i) / (image_width-1), 
                float(j) / (image_height-1),
                0.0f
            );
            // write the pixel to the image
            write_colour(std::cout, pixel_colour);
        }
    }

    std::clog << "\rDone.                 \n";
}