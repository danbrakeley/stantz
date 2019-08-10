#pragma once

#include "near.h"
#include <iostream>

class Vec3 {
public:
	Vec3() : e{0, 0, 0} {}
	Vec3(float e0, float e1, float e2) : e{e0, e1, e2} {}

	inline float x() const { return e[0]; }
	inline float y() const { return e[1]; }
	inline float z() const { return e[2]; }
	inline float r() const { return e[0]; }
	inline float g() const { return e[1]; }
	inline float b() const { return e[2]; }
	inline float operator[](int i) const { return e[i]; }
	inline float& operator[](int i) { return e[i]; };

	inline const Vec3& operator+() const { return *this; }
	inline Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }

	inline Vec3& operator+=(const Vec3& v);
	inline Vec3& operator-=(const Vec3& v);
	inline Vec3& operator*=(const Vec3& v);
	inline Vec3& operator/=(const Vec3& v);
	inline Vec3& operator*=(const float t);
	inline Vec3& operator/=(const float t);

	inline float length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
	inline float length_squared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
	inline Vec3 normalize() const;
	inline void normalize_in_place();

	static Vec3 random_in_unit_sphere();
	static Vec3 random_in_unit_disc();

private:
	float e[3];
};

inline std::istream& operator>>(std::istream& is, Vec3& v) {
	is >> v[0] >> v[1] >> v[2];
	return is;
}

inline std::ostream& operator<<(std::ostream& os, const Vec3& v) {
	os << v[0] << " " << v[1] << " " << v[2];
	return os;
}

inline Vec3 operator+(const Vec3& v, const Vec3& w) {
	return Vec3(v[0] + w[0], v[1] + w[1], v[2] + w[2]);
}

inline Vec3 operator-(const Vec3& v, const Vec3& w) {
	return Vec3(v[0] - w[0], v[1] - w[1], v[2] - w[2]);
}

inline Vec3 operator*(const Vec3& v, const Vec3& w) {
	return Vec3(v[0] * w[0], v[1] * w[1], v[2] * w[2]);
}

// inline Vec3 operator/(const Vec3& v, const Vec3& w) {
//	return Vec3(v[0] / w[0], v[1] / w[1], v[2] / w[2]);
//}

inline Vec3 operator*(float t, const Vec3& v) {
	return Vec3(t * v[0], t * v[1], t * v[2]);
}

inline Vec3 operator*(const Vec3& v, float t) {
	return t * v;
}

inline Vec3 operator/(const Vec3& v, float t) {
	return Vec3(v[0] / t, v[1] / t, v[2] / t);
}

inline float dot(const Vec3& v, const Vec3& w) {
	return v[0] * w[0] + v[1] * w[1] + v[2] * w[2];
}

inline Vec3 cross(const Vec3& v, const Vec3& w) {
	// clang-format off
	return Vec3(
		v[1]*w[2] - v[2]*w[1],
		v[2]*w[0] - v[0]*w[2],
		v[0]*w[1] - v[1]*w[0]
	);
	// clang-format on
}

inline Vec3& Vec3::operator+=(const Vec3& v) {
	e[0] += v[0];
	e[1] += v[1];
	e[2] += v[2];
	return *this;
}

inline Vec3& Vec3::operator-=(const Vec3& v) {
	e[0] -= v[0];
	e[1] -= v[1];
	e[2] -= v[2];
	return *this;
}

inline Vec3& Vec3::operator*=(const Vec3& v) {
	e[0] *= v[0];
	e[1] *= v[1];
	e[2] *= v[2];
	return *this;
}

inline Vec3& Vec3::operator/=(const Vec3& v) {
	e[0] /= v[0];
	e[1] /= v[1];
	e[2] /= v[2];
	return *this;
}

inline Vec3& Vec3::operator*=(const float t) {
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

inline Vec3& Vec3::operator/=(const float t) {
	float k = 1.0f / t;
	e[0] *= k;
	e[1] *= k;
	e[2] *= k;
	return *this;
}

inline Vec3 Vec3::normalize() const {
	Vec3 v = *this;
	v.normalize_in_place();
	return v;
}

inline void Vec3::normalize_in_place() {
	float k = 1.0f / length();
	e[0] *= k;
	e[1] *= k;
	e[2] *= k;
}

// "unsafe" because it is directly comparing floats
inline bool unsafe_equal(const Vec3& v, const Vec3& w) {
	return v[0] == w[0] && v[1] == w[1] && v[2] == w[2];
}

inline bool nearly_equal(const Vec3& v, const Vec3& w, float tol, float zero_tol) {
	// clang-format off
	return
		nearly_equal(v[0], w[0], tol, zero_tol) &&
		nearly_equal(v[1], w[1], tol, zero_tol) &&
		nearly_equal(v[2], w[2], tol, zero_tol);
	// clang-format on
}

inline Vec3 reflect(const Vec3& v, const Vec3& normal) {
	return v - (2.0f * dot(v, normal) * normal);
}

bool refract(const Vec3& v, const Vec3& normal, float ni_over_nt, Vec3* p_refracted);
