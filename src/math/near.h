#pragma once

#include <algorithm>
#include <limits>

template<class T>
inline bool nearly_zero(T x, T zero_tolerance) {
	return std::abs(x) < zero_tolerance;
}

// from https://www.reidatcheson.com/floating%20point/comparison/2019/03/20/floating-point-comparison.html

template<class T>
bool nearly_equal(T x, T y, T tolerance, T zero_tolerance) {
	float min = std::min(std::abs(x), std::abs(y));
	if (std::abs(min) == 0) {
		return nearly_zero(x - y, zero_tolerance);
	}

	// Threshold denominator so we don't divide by zero
	constexpr T threshold = std::numeric_limits<T>::min(); // A very small nonzero number!
	return (std::abs(x - y) / std::max(threshold, min)) < tolerance;
}
