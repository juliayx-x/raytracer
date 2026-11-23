#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

// does the ray hit the sphere at all? solve |P(t) - center|^2 = r^2 for t
// and just check the discriminant. negative = no real roots = miss
bool hits_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = center - r.origin();

    double a = dot(r.direction(), r.direction());
    double b = -2.0 * dot(r.direction(), oc);
    double c = dot(oc, oc) - radius * radius;

    return b * b - 4 * a * c >= 0;
}


    for (int j = 0; j < height; ++j) {
        std::clog << "\rScanlines remaining: " << (height - j) << ' ' << std::flush;

        for (int i = 0; i < width; ++i) {
            point3 pixel = first_pixel + i * du + j * dv;
            ray r(eye, pixel - eye);
            write_color(std::cout, ray_color(r));
        }
    }

    std::clog << "\rDone.                 \n";
}