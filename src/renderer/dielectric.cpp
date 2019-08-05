#pragma once

#include "pch.h"
#include "dielectric.h"
#include "rand.h"
#include <math.h>

// Christophe Schlick's polynomial approximation of how real glass has reflectivity that varies with angle
float schlick(float cosine, float reflection_index) {
	float r0 = (1 - reflection_index) / (1 + reflection_index);
	r0 *= r0;
	return r0 + (1 - r0) * powf(1 - cosine, 5);
}

bool Dielectric::scatter(const Ray& r_in, const hit_record& rec, Vec3* p_attenuation, Ray* p_scattered) const {
	assert(p_scattered != nullptr);
	assert(p_attenuation != nullptr);

	Vec3 outward_normal;
	float ni_over_nt;
	float cosine;
	float r_in_dot_normal = dot(r_in.direction(), rec.normal);
	if (r_in_dot_normal > 0) {
		outward_normal = -rec.normal;
		ni_over_nt = ri_;
		cosine = ri_ * r_in_dot_normal / r_in.direction().length();
	} else {
		outward_normal = rec.normal;
		ni_over_nt = 1.0f / ri_;
		cosine = -r_in_dot_normal / r_in.direction().length();
	}

	Vec3 refracted;
	bool did_refract = refract(r_in.direction(), outward_normal, ni_over_nt, &refracted);

	float reflect_prob = 1;
	if (did_refract) {
		reflect_prob = schlick(cosine, ri_);
	}

	*p_attenuation = Vec3(1, 1, 1);

	if (rand_unit<float>() < reflect_prob) {
		*p_scattered = Ray(rec.point, reflect(r_in.direction(), rec.normal));
	} else {
		*p_scattered = Ray(rec.point, refracted);
	}

	return true;
}
