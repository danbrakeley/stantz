#pragma once

#include "hitable.h"
#include "material.h"
#include "ray.h"
#include "vec3.h"

class Lambertian : public Material {
public:
	Lambertian(const Vec3& albedo) : m_albedo(albedo) {}

	virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec3* p_atten, Ray* p_scattered) const override;

private:
	Vec3 m_albedo;
};
