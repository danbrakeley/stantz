#pragma once

#include "ray.h"
#include "vec3.h"

struct hit_record {
	float t;
	vec3 point;
	vec3 normal;
};

class hitable {
public:
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record* p_rec) const = 0;
};
