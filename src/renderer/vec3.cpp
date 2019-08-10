#pragma once

#include "pch.h"
#include "vec3.h"
#include "rand.h"

Vec3 Vec3::random_in_unit_sphere() {
	// TODO: could this be faster somehow?
	// https://blog.joeardent.net/2018/07/right-and-wrong-ways-to-pick-random-points-inside-a-sphere/
	Vec3 p;
	do {
		p = 2.0f * Vec3(rand_unit<float>(), rand_unit<float>(), rand_unit<float>()) - Vec3(1, 1, 1);
	} while (p.length_squared() >= 1);
	return p;
}

Vec3 Vec3::random_in_unit_disc() {
	Vec3 p;
	do {
		p = 2 * Vec3(rand_unit<float>(), rand_unit<float>(), 0) - Vec3(1, 1, 0);
	} while (p.length_squared() >= 1);
	return p;
}

bool refract(const Vec3& v, const Vec3& normal, float ni_over_nt, Vec3* p_refracted) {
	Vec3 uv = v.normalize();
	float dt = dot(uv, normal);
	float discriminant = 1 - ni_over_nt * ni_over_nt * (1 - dt * dt);
	if (discriminant > 0) {
		*p_refracted = ni_over_nt * (uv - normal * dt) - normal * sqrt(discriminant);
		return true;
	}
	return false;
}
