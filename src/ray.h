#pragma once

#include "vec3.h"

class ray {
public:
	ray() {}
	ray(const vec3& origin, const vec3& direction) : m_origin(origin), m_direction(direction) {}

	vec3 origin() const { return m_origin; }
	vec3 direction() const { return m_direction; }

	vec3 point(float t) const { return m_origin + t * m_direction; }

private:
	vec3 m_origin;
	vec3 m_direction;
};
