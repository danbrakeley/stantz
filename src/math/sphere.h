#pragma once

#include "hitable.h"
#include "vec3.h"

class sphere : public hitable {
public:
	sphere() : m_center(), m_radius(0) {}
	sphere(vec3 center, float radius) : m_center(center), m_radius(radius) {}

	virtual bool hit(const ray& r, float t_min, float t_max, hit_record* rec) const;

private:
	vec3 m_center;
	float m_radius;
};
