#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "sphere.h"
#include "hittableList.h"
#include "utilities.h"
#include "camera.h"
#include "material.h"

#include <iostream>
#include <memory>

Color ray_color(const Ray& r, const HittableList& world, int depth) {
    HitRecord rec;

    // Exceeded max number of ray bounces, return no color
    if (depth <= 0) {
        return Color(0, 0, 0);
    }

    // std::cerr << "depth: " << depth << std::endl;
    // Color if hit object
    // Ignore hits very near zero
    if (world.hit(r, 0.001, INF, rec)) {
        // Color of normal
        // return 0.5*Color(rec.normal.x()+1, rec.normal.y()+1, rec.normal.z()+1);

        // Diffuse reflection before we moved all this into material.h
        // Reflection off diffuse surface
        // Point3 spherePoint = rec.p + rec.normal + random_unit_vector();

        // Vec3 newDir = spherePoint - rec.p;
        // Ray newRay(rec.p, newDir);
        // // Color contribution lessens with each bounce
        // return 0.5 * ray_color(newRay, world, depth - 1);

        Ray rOut;
        Color attenuation;

        if (rec.matPtr->scatter(r, rec, attenuation, rOut)) {
            // std::cerr << "HERE " << rOut.direction().x() << ", " << rOut.direction().y() << ", " << rOut.direction().z() << std::endl;

            // std::cerr << "asdf " << rOut.direction().x() << std::endl;
            // std::cerr << "HERE " << depth << std::endl;
            // Color temp = ray_color(rOut, world, depth - 1);
            // std::cerr << "asdf" << std::endl;
            // What does it mean to multiply a Color by another Color?
            return attenuation;
            // return attenuation * ray_color(rOut, world, depth - 1);
        }

        // Failed to scatter (light was absorbed?)
        return Color(0, 0, 0);
    }

    // Background color (gradient along y axis from blue to white)
    Vec3 unit_direction = unit_vector(r.direction());
    // -1.0 < y < 1.0
    // converts to
    // 0.0 <= t <= 1.0
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
}


int main() {

    // Part 1
    // // Image

    // const int image_width = 256;
    // const int image_height = 256;

    // // Render

    // std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    // for (int j = image_height-1; j >= 0; --j) {
    //     std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    //     for (int i = 0; i < image_width; ++i) {
    //         auto r = double(i) / (image_width-1);
    //         auto g = double(j) / (image_height-1);
    //         auto b = 0.25;
    //         Color pixel_color(r, g, b);
    //         write_color(std::cout, pixel_color);
    //     }
        
    // }
    // std::cerr << "\nDone.\n";

    // --------------------------------
    // // Part 2
    // // Image
    // const auto aspect_ratio = 16.0 / 9.0;
    // const int image_width = 400;
    // const int image_height = static_cast<int>(image_width / aspect_ratio);

    // // Camera
    // auto viewport_height = 2.0;
    // auto viewport_width = aspect_ratio * viewport_height;
    // auto focal_length = 1.0;

    // auto origin = Point3(0, 0, 0);
    // auto horizontal = Vec3(viewport_width, 0, 0);
    // auto vertical = Vec3(0, viewport_height, 0);
    // auto lower_left_corner = origin - horizontal/2 - vertical/2 - Vec3(0, 0, focal_length);

    // // Render

    // std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    // for (int j = image_height-1; j >= 0; --j) {
    //     std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    //     for (int i = 0; i < image_width; ++i) {
    //         auto u = double(i) / (image_width-1);
    //         auto v = double(j) / (image_height-1);
    //         Ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
    //         Color pixel_color = ray_color(r);
    //         write_color(std::cout, pixel_color);
    //     }
    // }

    // std::cerr << "\nDone.\n";

    // --------------------------------
    // // Part 3
    // // Image
    // const auto aspect_ratio = 16.0 / 9.0;
    // const int image_width = 400;
    // const int image_height = static_cast<int>(image_width / aspect_ratio);

    // // Camera
    // auto viewport_height = 2.0;
    // auto viewport_width = aspect_ratio * viewport_height;
    // auto focal_length = 1.0;

    // auto origin = Point3(0, 0, 0);
    // auto horizontal = Vec3(viewport_width, 0, 0);
    // auto vertical = Vec3(0, viewport_height, 0);
    // auto lower_left_corner = origin - horizontal/2 - vertical/2 - Vec3(0, 0, focal_length);

    // // World
    // HittableList world;
    // world.addObject(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    // world.addObject(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // // Render
    // std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    // for (int j = image_height-1; j >= 0; --j) {
    //     std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    //     for (int i = 0; i < image_width; ++i) {
    //         auto u = double(i) / (image_width-1);
    //         auto v = double(j) / (image_height-1);
    //         Ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
    //         Color pixel_color = ray_color(r, world);
    //         write_color(std::cout, pixel_color);
    //     }
    // }

    // std::cerr << "\nDone.\n";

    // --------------------------------
    // Part 4
    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int maxDepth = 2;

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;
    auto origin = Point3(0, 0, 0);
    Camera cam(origin, viewport_height, viewport_width, focal_length);

    // World
    HittableList world;
    auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
    // auto material_left   = std::make_shared<Metal>(Color(0.8, 0.8, 0.8));
    // auto material_right  = std::make_shared<Metal>(Color(0.8, 0.6, 0.2));

    // Ground sphere
    world.addObject(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
    // Smaller spheres
     // world.addObject(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5, material_center));
     // world.addObject(std::make_shared<Sphere>(Point3(-1, 0, -1), 0.5, material_left));
     // world.addObject(std::make_shared<Sphere>(Point3(1, 0, -1), 0.5, material_right));

    // Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            // Sample within pixel for anti-aliasing
            Color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = double(i + random_double()) / (image_width-1);
                auto v = double(j + random_double()) / (image_height-1);
                Ray r = cam.getRay(u, v);
                pixel_color += ray_color(r, world, maxDepth);
            }
            writeColor(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";


}