#pragma once

#include "ray.h"
#include "vec3.h"

class Material;

struct hit_record {
	float t;
	Vec3 point;
	Vec3 normal;
	Material* p_mat;
};

class Hitable {
public:
	virtual bool hit(const Ray& r, float t_min, float t_max, hit_record* p_rec) const = 0;
};
