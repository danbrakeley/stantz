#pragma once

#include "hitable.h"
#include "ray.h"
#include "vec3.h"

class Sphere : public Hitable {
public:
	Sphere() : m_center(), m_radius(0) {}
	Sphere(Vec3 center, float radius) : m_center(center), m_radius(radius) {}

	virtual bool hit(const Ray& r, float t_min, float t_max, hit_record* p_rec) const override;

private:
	Vec3 m_center;
	float m_radius;
};
