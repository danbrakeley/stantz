#pragma once

#include "math.h"
#include "ray.h"
#include "vec3.h"

class Camera {
public:
	Camera() {}
	Camera(const Vec3& lookfrom, const Vec3& lookat, const Vec3& up, float vfov, float aspect) {
		Vec3 u, v, w;
		float theta = deg_to_rad(vfov);
		float half_height = tanf(theta / 2);
		float half_width = aspect * half_height;
		origin_ = lookfrom;
		w = (lookfrom - lookat).normalize();
		u = cross(up, w).normalize();
		v = cross(w, u);
		lower_left_ = origin_ - half_width * u - half_height * v - w;
		horiz_ = 2 * half_width * u;
		vert_ = 2 * half_height * v;
	}

	Ray get_ray(float u, float v) const { return Ray(origin_, lower_left_ + u * horiz_ + v * vert_ - origin_); }

private:
	Vec3 origin_;
	Vec3 lower_left_;
	Vec3 horiz_;
	Vec3 vert_;
};
