#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

#include <memory>

class Sphere : public Hittable {
	public:
		Sphere() {}
		Sphere(Point3 center, double radius, std::shared_ptr<Material> matPtr)
            : center_(center), radius_(radius), matPtr_(matPtr) {}

		virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

		Point3 center_;
		double radius_;
        std::shared_ptr<Material> matPtr_;


	protected:	
};

bool Sphere::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
	// Calculating discriminant for quadratic equation
    Vec3 oc = r.origin() - center_;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius_*radius_;
    auto discriminant = (half_b*half_b) - a*c;
    if (discriminant < 0) {
        return false;
    }

    // Calculate closest/smallest hit point
    auto sqrtd = sqrt(discriminant);
    auto root = (-half_b - sqrtd) / a;

    auto notWithinInterval = [t_min, t_max](double root) { return (root < t_min || root > t_max); };
    if (notWithinInterval(root)) {
    	root = (-half_b + sqrtd) / a;
    	if (notWithinInterval(root)) {
    		return false;
    	}
    }

    // Update HitRecord
    rec.t = root;
    rec.p = r.at(rec.t);
    // This normal always points outward
    Vec3 outwardNormal = unit_vector(rec.p - center_);
    rec.set_face_normal(r, outwardNormal);
    rec.matPtr = matPtr_;
    return true;
}

#endif