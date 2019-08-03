#include "pch.h"
#include "sphere.h"

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record* rec) const {
	assert(rec != nullptr);

	vec3 oc = r.origin() - m_center;
	float a = dot(r.direction(), r.direction());
	// the 2 from b was removed because it doesn't impact how we use the discriminant, and cancels in the final quadratic
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - m_radius * m_radius;
	// discriminant determines how many roots:
	//  < 0 == 0 roots (can't sqrt a negative number)
	//  = 0 == 1 root (ignore as a possible hit?)
	//  > 0 == 2 roots
	float discriminant = b * b - a * c;
	if (discriminant > 0) {
		// some 2's are missing because we cancelled them with b's 2
		float temp = (-b - sqrt(discriminant)) / a;
		if (temp < t_max && temp > t_min) {
			rec->t = temp;
			rec->point = r.point(rec->t);
			// normal is center to point on sphere (aka point of intersection we just calculated)
			// and radius is the length of any vector from the center to the surface, so skip a sqrt
			rec->normal = (rec->point - m_center) / m_radius;
			return true;
		}
		// if the above closest root wasn't in the range we want, try again for second root
		temp = (-b + sqrt(discriminant)) / a;
		if (temp < t_max && temp > t_min) {
			rec->t = temp;
			rec->point = r.point(rec->t);
			rec->normal = (rec->point - m_center) / m_radius;
			return true;
		}
	}

	return false;
}
