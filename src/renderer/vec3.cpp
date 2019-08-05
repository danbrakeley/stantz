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
