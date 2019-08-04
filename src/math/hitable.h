#pragma once

#include "ray.h"
#include "vec3.h"

struct hit_record {
	float t;
	Vec3 point;
	Vec3 normal;
};

class Hitable {
public:
	virtual bool hit(const Ray& r, float t_min, float t_max, hit_record* p_rec) const = 0;
};
