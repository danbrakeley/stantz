#pragma once

#include "hitable.h"
#include "material.h"
#include "ray.h"
#include "vec3.h"

class Metal : public Material {
public:
	Metal(const Vec3& albedo, float fuzz) : albedo_(albedo), fuzz_(fuzz) {}

	virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec3* p_atten, Ray* p_scattered) const override;

private:
	Vec3 albedo_;
	float fuzz_;
};
