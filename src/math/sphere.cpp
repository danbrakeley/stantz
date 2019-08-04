#include "pch.h"
#include "sphere.h"

bool Sphere::hit(const Ray& r, float t_min, float t_max, hit_record* p_rec) const {
	assert(p_rec != nullptr);
	assert(p_mat_ != nullptr);

	Vec3 oc = r.origin() - center_;
	float a = dot(r.direction(), r.direction());
	// the 2 from b was removed because it doesn't impact how we use the discriminant, and cancels in the final quadratic
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius_ * radius_;
	// discriminant determines how many roots:
	//  < 0 == 0 roots (can't sqrt a negative number)
	//  = 0 == 1 root (ignore as a possible hit?)
	//  > 0 == 2 roots
	float discriminant = b * b - a * c;
	if (discriminant > 0) {
		// some 2's are missing because we cancelled them with b's 2
		float temp = (-b - sqrt(discriminant)) / a;
		if (temp < t_max && temp > t_min) {
			p_rec->t = temp;
			p_rec->point = r.point(p_rec->t);
			// normal is center to point on sphere (aka point of intersection we just calculated)
			// and radius is the length of any vector from the center to the surface, so skip a sqrt
			p_rec->normal = (p_rec->point - center_) / radius_;
			p_rec->p_mat = p_mat_;
			return true;
		}
		// if the above closest root wasn't in the range we want, try again for second root
		temp = (-b + sqrt(discriminant)) / a;
		if (temp < t_max && temp > t_min) {
			p_rec->t = temp;
			p_rec->point = r.point(p_rec->t);
			p_rec->normal = (p_rec->point - center_) / radius_;
			p_rec->p_mat = p_mat_;
			return true;
		}
	}

	return false;
}
