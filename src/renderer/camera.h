#pragma once

#include "math.h"
#include "ray.h"
#include "vec3.h"

class Camera {
public:
	virtual Ray get_ray(float u, float v) const = 0;
};

class PinholeCamera : public Camera {
public:
	PinholeCamera() {}
	PinholeCamera(const Vec3& lookfrom, const Vec3& lookat, const Vec3& up, float vfov, float aspect) {
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

	virtual Ray get_ray(float u, float v) const override {
		return Ray(origin_, lower_left_ + u * horiz_ + v * vert_ - origin_);
	}

private:
	Vec3 origin_;
	Vec3 lower_left_;
	Vec3 horiz_;
	Vec3 vert_;
};

class DofCamera : public Camera {
public:
	DofCamera() : lens_radius_(0) {}
	DofCamera(
	  const Vec3& lookfrom,
	  const Vec3& lookat,
	  const Vec3& up,
	  float vfov,
	  float aspect,
	  float aperture,
	  float focus_dist) {
		lens_radius_ = aperture / 2;
		float theta = deg_to_rad(vfov);
		float half_height = tanf(theta / 2);
		float half_width = aspect * half_height;
		origin_ = lookfrom;
		w_ = (lookfrom - lookat).normalize();
		u_ = cross(up, w_).normalize();
		v_ = cross(w_, u_);
		lower_left_ = origin_ - half_width * focus_dist * u_ - half_height * focus_dist * v_ - focus_dist * w_;
		horiz_ = 2 * half_width * focus_dist * u_;
		vert_ = 2 * half_height * focus_dist * v_;
	}

	Ray get_ray(float s, float t) const {
		Vec3 rd = lens_radius_ * Vec3::random_in_unit_disc();
		Vec3 offset = u_ * rd.x() + v_ * rd.y();
		return Ray(origin_ + offset, lower_left_ + s * horiz_ + t * vert_ - origin_ - offset);
	}

private:
	Vec3 origin_;
	Vec3 lower_left_;
	Vec3 horiz_;
	Vec3 vert_;
	Vec3 u_, v_, w_;
	float lens_radius_;
};
