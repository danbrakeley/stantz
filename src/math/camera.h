#pragma once

#include "ray.h"
#include "vec3.h"

class camera {
public:
	camera() : m_lower_left(-2, -1, -1), m_horiz(4, 0, 0), m_vert(0, 2, 0), m_origin(0, 0, 0) {}
	ray get_ray(float u, float v) const { return ray(m_origin, m_lower_left + u * m_horiz + v * m_vert - m_origin); }

private:
	vec3 m_origin;
	vec3 m_lower_left;
	vec3 m_horiz;
	vec3 m_vert;
};
