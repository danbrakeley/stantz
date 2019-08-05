#pragma once

#include "vec3.h"

class Ray {
public:
	Ray() {}
	Ray(const Vec3& origin, const Vec3& direction) : m_origin(origin), m_direction(direction) {}

	Vec3 origin() const { return m_origin; }
	Vec3 direction() const { return m_direction; }

	Vec3 point(float t) const { return m_origin + t * m_direction; }

private:
	Vec3 m_origin;
	Vec3 m_direction;
};
