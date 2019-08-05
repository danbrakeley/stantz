#pragma once

#include "pch.h"
#include "lambertian.h"

bool Lambertian::scatter(const Ray& r_in, const hit_record& rec, Vec3* p_attenuation, Ray* p_scattered) const {
	assert(p_scattered != nullptr);
	assert(p_attenuation != nullptr);

	Vec3 target = rec.point + rec.normal + Vec3::random_in_unit_sphere();
	*p_scattered = Ray(rec.point, target - rec.point);
	*p_attenuation = m_albedo;
	return true;
}
