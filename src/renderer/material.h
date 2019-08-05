#pragma once

#include "hitable.h"
#include "ray.h"
#include "vec3.h"

class Material {
public:
	virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec3* p_atten, Ray* p_scattered) const = 0;
};
