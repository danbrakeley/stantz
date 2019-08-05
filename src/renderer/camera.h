#pragma once

#include "ray.h"
#include "vec3.h"

class Camera {
public:
	Camera() : m_lower_left(-2, -1, -1), m_horiz(4, 0, 0), m_vert(0, 2, 0), m_origin(0, 0, 0) {}
	Ray get_ray(float u, float v) const { return Ray(m_origin, m_lower_left + u * m_horiz + v * m_vert - m_origin); }

private:
	Vec3 m_origin;
	Vec3 m_lower_left;
	Vec3 m_horiz;
	Vec3 m_vert;
};
