#pragma once

#include "hitable.h"
#include "ray.h"
#include "vec3.h"

class Sphere : public Hitable {
public:
	Sphere() : center_(), radius_(0), p_mat_(nullptr) {}
	Sphere(Vec3 center, float radius, Material* p_mat) : center_(center), radius_(radius), p_mat_(p_mat) {}

	virtual bool hit(const Ray& r, float t_min, float t_max, hit_record* p_rec) const override;

private:
	Vec3 center_;
	float radius_;
	Material* p_mat_;
};
