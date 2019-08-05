#pragma once

#include "hitable.h"
#include "material.h"
#include "ray.h"
#include "vec3.h"

class Dielectric : public Material {
public:
	Dielectric(float reflective_index) : ri_(reflective_index) {}

	virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec3* p_atten, Ray* p_scattered) const override;

private:
	float ri_;
};
