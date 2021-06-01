#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"

class Camera {
	public:
		Camera(Point3 origin, double viewportHeight, double viewportWidth, double focalLength) : origin_(origin) {
			horizontal_ = Vec3(viewportWidth, 0, 0);
    		vertical_ = Vec3(0, viewportHeight, 0);
    		lowerLeftCorner_ = origin - horizontal_/2 - vertical_/2 - Vec3(0, 0, focalLength);
		}

		Ray getRay(double u, double v) const {
			return Ray(origin_, lowerLeftCorner_ + u*horizontal_ + v*vertical_ - origin_);
		}


	private:
		Point3 origin_;
		Vec3 horizontal_;
		Vec3 vertical_;
		Vec3 lowerLeftCorner_;

	protected:
};


#endif