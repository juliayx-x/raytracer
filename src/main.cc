#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

// returns the t where the ray first hits the sphere, or -1 if it misses
double hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = center - r.origin();
    double a = r.direction().length_squared();
    double h = dot(r.direction(), oc);          // b = -2h, so the 2s and 4 cancel
    double c = oc.length_squared() - radius * radius;

    double disc = h * h - a * c;
    if (disc < 0) return -1.0;
    return (h - std::sqrt(disc)) / a;           // smaller root = closer hit
}

color ray_color(const ray& r) {
    double t = hit_sphere(point3(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
        return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    vec3 dir = unit_vector(r.direction());
    double a = 0.5 * (dir.y() + 1.0);   // y is in [-1,1], squash to [0,1]
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main() {
    //image
    const double aspect_ratio = 16.0 / 9.0;
    const int width = 400;
    int height = int(width / aspect_ratio);
    if (height < 1) height = 1;

    //camera
    // viewport = the rectangle in 3D space the image gets projected onto.
    // use the real width/height ratio since height got rounded
    const double focal_length = 1.0;
    const double view_h = 2.0;
    const double view_w = view_h * (double(width) / height);
    const point3 eye(0, 0, 0);

    // edges of the viewport. v points down because pixel rows go top -> bottom
    vec3 across(view_w, 0, 0);
    vec3 down(0, -view_h, 0);

    // step between neighbouring pixels
    vec3 du = across / width;
    vec3 dv = down / height;

    // camera looks down -z. find the top-left corner, then nudge half a pixel
    // in so rays go through pixel centres instead of corners
    point3 top_left = eye - vec3(0, 0, focal_length) - across / 2 - down / 2;
    point3 first_pixel = top_left + 0.5 * (du + dv);

    //render
    std::cout << "P3\n" << width << ' ' << height << "\n255\n";

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