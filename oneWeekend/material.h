#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec3.h"
#include "ray.h"
#include "util.h"

#include <iostream>

// Stub to avoid cyclical reference to hittable.h
struct HitRecord;

class Material {
	public:
		// const at the end means it doesn't modify anything inside class
		// = 0 means it is a pure virtual method -- must be derived in child class
		virtual bool scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& rOut) const = 0;

		// Vec3 reflect(const Vec3& vIn, const Vec3& normal) const {
		//     return vIn - 2 * dot(vIn, normal) * normal;
		// }

};


class Lambertian : public Material {
public:
	Lambertian(const Color& albedo) : albedo_(albedo) {}

	// Use virtual here to make sure method is bound at run-time based on content of pointer
	virtual bool scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& rOut) const override {
		Vec3 scatterDir = rec.normal + random_unit_vector();

		// If random unit vector is exactly opposite rec.normal, could result in zero scatter dir
		if (scatterDir.near_zero()) {
			scatterDir = rec.normal;
		}

		rOut = Ray(rec.p, scatterDir);
		// std::cerr << rOut.direction().x() << std::endl;
		attenuation = albedo_;

		return true;
	}

	// Albedo is color of object
	Color albedo_;

};


// // Metal just reflects rays
// class Metal : public Material {
// public:
// 	Metal(const Color& albedo) : albedo_(albedo) {}

// 	virtual bool scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& rOut) const override {
// 		Vec3 reflectDir = reflect(unit_vector(rIn.direction()), rec.normal);
// 		rOut = Ray(rec.p, reflectDir);
// 		attenuation = albedo_;
// 		// Return false if angle between reflected ray and normal is >= 90 degrees
// 		// Doesn't this mean that rIn would also be >= 90 degrees though?
// 		// Does this just mean it was absorbed?
// 		return (dot(rOut.direction(), rec.normal) > 0);
// 	}

// private:
// 	Color albedo_;
// };

#endif