#pragma once

#include "near.h"

class vec3 {
public:
	vec3() : e{0, 0, 0} {}
	vec3(float e0, float e1, float e2) {
		e[0] = e0;
		e[1] = e1;
		e[2] = e2;
	}

	inline float x() const { return e[0]; }
	inline float y() const { return e[1]; }
	inline float z() const { return e[2]; }
	inline float r() const { return e[0]; }
	inline float g() const { return e[1]; }
	inline float b() const { return e[2]; }
	inline float operator[](int i) const { return e[i]; }
	inline float& operator[](int i) { return e[i]; };

	inline const vec3& operator+() const { return *this; }
	inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

	inline vec3& operator+=(const vec3& v);
	inline vec3& operator-=(const vec3& v);
	inline vec3& operator*=(const vec3& v);
	inline vec3& operator/=(const vec3& v);
	inline vec3& operator*=(const float t);
	inline vec3& operator/=(const float t);

	inline float length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
	inline float length_squared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
	inline vec3 normalize() const;
	inline void normalize_in_place();

private:
	float e[3];
};

inline std::istream& operator>>(std::istream& is, vec3& v) {
	is >> v[0] >> v[1] >> v[2];
	return is;
}

inline std::ostream& operator<<(std::ostream& os, const vec3& v) {
	os << v[0] << " " << v[1] << " " << v[2];
	return os;
}

inline vec3 operator+(const vec3& v, const vec3& w) {
	return vec3(v[0] + w[0], v[1] + w[1], v[2] + w[2]);
}

inline vec3 operator-(const vec3& v, const vec3& w) {
	return vec3(v[0] - w[0], v[1] - w[1], v[2] - w[2]);
}

// inline vec3 operator*(const vec3& v, const vec3& w) {
//	return vec3(v[0] * w[0], v[1] * w[1], v[2] * w[2]);
//}

// inline vec3 operator/(const vec3& v, const vec3& w) {
//	return vec3(v[0] / w[0], v[1] / w[1], v[2] / w[2]);
//}

inline vec3 operator*(float t, const vec3& v) {
	return vec3(t * v[0], t * v[1], t * v[2]);
}

inline vec3 operator*(const vec3& v, float t) {
	return t * v;
}

inline vec3 operator/(const vec3& v, float t) {
	return vec3(v[0] / t, v[1] / t, v[2] / t);
}

inline float dot(const vec3& v, const vec3& w) {
	return v[0] * w[0] + v[1] * w[1] + v[2] * w[2];
}

inline vec3 cross(const vec3& v, const vec3& w) {
	// clang-format off
	return vec3(
		v[1]*w[2] - v[2]*w[1],
		v[2]*w[0] - v[0]*w[2],
		v[0]*w[1] - v[1]*w[0]
	);
	// clang-format on
}

inline vec3& vec3::operator+=(const vec3& v) {
	e[0] += v[0];
	e[1] += v[1];
	e[2] += v[2];
	return *this;
}

inline vec3& vec3::operator-=(const vec3& v) {
	e[0] -= v[0];
	e[1] -= v[1];
	e[2] -= v[2];
	return *this;
}

inline vec3& vec3::operator*=(const vec3& v) {
	e[0] *= v[0];
	e[1] *= v[1];
	e[2] *= v[2];
	return *this;
}

inline vec3& vec3::operator/=(const vec3& v) {
	e[0] /= v[0];
	e[1] /= v[1];
	e[2] /= v[2];
	return *this;
}

inline vec3& vec3::operator*=(const float t) {
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

inline vec3& vec3::operator/=(const float t) {
	float k = 1.0f / t;
	e[0] *= k;
	e[1] *= k;
	e[2] *= k;
	return *this;
}

inline vec3 vec3::normalize() const {
	vec3 v = *this;
	v.normalize_in_place();
	return v;
}

inline void vec3::normalize_in_place() {
	float k = 1.0f / length();
	e[0] *= k;
	e[1] *= k;
	e[2] *= k;
}

// "unsafe" because it is directly comparing floats
inline bool unsafe_equal(const vec3& v, const vec3& w) {
	return v[0] == w[0] && v[1] == w[1] && v[2] == w[2];
}

inline bool almost_equal(const vec3& v, const vec3& w, float tol, float zero_tol) {
	// clang-format off
	return
		almost_equal(v[0], w[0], tol, zero_tol) &&
		almost_equal(v[1], w[1], tol, zero_tol) &&
		almost_equal(v[2], w[2], tol, zero_tol);
	// clang-format on
}
