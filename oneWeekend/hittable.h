#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

#include <memory>

// Stub to avoid cyclical reference to material.h
class Material;

struct HitRecord {
    Point3 p;
    Vec3 normal;
    std::shared_ptr<Material> matPtr;
    double t;
    bool isRayOutside;

    inline void set_face_normal(const Ray& r, const Vec3& outward_normal) {
    	// Update normal to point outwards if ray is outside surface
    	// or to point inwards if ray is inside surface
        isRayOutside = dot(r.direction(), outward_normal) < 0;
        normal = isRayOutside ? outward_normal : -outward_normal;
    }
};

class Hittable {
    public:
        virtual bool hit(const Ray& r, const double t_min, const double t_max, HitRecord& rec) const = 0;
};

#endif