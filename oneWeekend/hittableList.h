#ifndef HITTABLELIST_H
#define HITTABLELIST_H

#include "hittable.h"

#include <memory>
#include <vector>

class HittableList: public Hittable {
	public:
		HittableList() {}
		HittableList(std::shared_ptr<Hittable> obj) { addObject(obj); }

		void addObject(std::shared_ptr<Hittable> obj) { objects_.push_back(obj); }

		void clear() { objects_.clear(); }

        virtual bool hit(const Ray& r, const double t_min, const double t_max, HitRecord& rec) const override;

	private:
		std::vector<std::shared_ptr<Hittable>> objects_;

	protected:
};

bool HittableList::hit(const Ray& r, const double t_min, const double t_max, HitRecord& rec) const {
	bool objHit;
	double closestT = t_max;
	HitRecord tempRec;

	// Get closest object hit
	for (const auto& obj : objects_) {
		if (obj->hit(r, t_min, closestT, tempRec)) {
			objHit = true;
			closestT = tempRec.t;
			rec = tempRec;
		}
	}

	return objHit;
}

#endif