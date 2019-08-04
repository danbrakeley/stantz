#pragma once

#include "pch.h"
#include "metal.h"

bool Metal::scatter(const Ray& r_in, const hit_record& rec, Vec3* p_attenuation, Ray* p_scattered) const {
	assert(p_scattered != nullptr);
	assert(p_attenuation != nullptr);

	Vec3 reflected = reflect(r_in.direction().normalize(), rec.normal);
	*p_scattered = Ray(rec.point, reflected + fuzz_ * Vec3::random_in_unit_sphere());
	*p_attenuation = albedo_;
	return (dot(p_scattered->direction(), rec.normal) > 0);
}
