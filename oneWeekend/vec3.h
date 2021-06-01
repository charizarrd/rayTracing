#ifndef VEC3_H
#define VEC3_H

#include "utilities.h"

#include <cmath>
#include <iostream>

using std::sqrt;

class Vec3 {
    public:
        Vec3() : e{0,0,0} {}
        Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        Vec3& operator+=(const Vec3 &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        Vec3& operator*=(const double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        Vec3& operator/=(const double t) {
            return *this *= 1/t;
        }

        double length() const {
            return sqrt(length_squared());
        }

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        inline static Vec3 random() {
            return Vec3(random_double(), random_double(), random_double());
        }

        inline static Vec3 random(double min, double max) {
            return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }

        bool near_zero() const {
            // Return true if vector is close to zero in all dimensions
            const auto tolerance = 1e-8;
            return (fabs(e[0]) < tolerance) && (fabs(e[1]) < tolerance) && (fabs(e[2]) < tolerance);
        }


        double e[3];
};

// Type aliases for Vec3
using Point3 = Vec3;   // 3D point
using Color = Vec3;    // RGB color

// Vec3 Utility Functions

inline std::ostream& operator<<(std::ostream &out, const Vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vec3 operator*(double t, const Vec3 &v) {
    return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline Vec3 operator*(const Vec3 &v, double t) {
    return t * v;
}

inline Vec3 operator/(Vec3 v, double t) {
    return (1/t) * v;
}

// dot product = how much u and v are in same direction
inline double dot(const Vec3 &u, const Vec3 &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

// cross product = perpendicular to both u and v
inline Vec3 cross(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

// unit vector = has magnitude of one
inline Vec3 unit_vector(Vec3 v) {
    return v / v.length();
}

Vec3 random_in_unit_sphere() {
    // Randomly sample points in a unit cube where x, y, z [-1, 1] and check if it is within a circle of radius 1
    while(true) {
        Vec3 randomVec = Vec3::random(-1, 1);
        if (randomVec.length_squared() >= 1) {
            continue;
        }
        return randomVec;
    }
}

Vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

#endif