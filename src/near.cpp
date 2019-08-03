#pragma once

#include "pch.h"
#include "near.h"
#include <algorithm>
#include <limits>

// from https://www.reidatcheson.com/floating%20point/comparison/2019/03/20/floating-point-comparison.html

bool almost_equal(float x, float y, float tolerance, float zero_tolerance) {
	float min = std::min(std::abs(x), std::abs(y));
	if (std::abs(min) == 0.0) {
		return std::abs(x - y) < zero_tolerance;
	}

	// Threshold denominator so we don't divide by zero
	constexpr float threshold = std::numeric_limits<float>::min(); // A very small nonzero number!
	return (std::abs(x - y) / std::max(threshold, min)) < tolerance;
}

bool almost_equal(double x, double y, double tolerance, double zero_tolerance) {
	double min = std::min(std::abs(x), std::abs(y));
	if (std::abs(min) == 0.0) {
		return std::abs(x - y) < zero_tolerance;
	}

	// Threshold denominator so we don't divide by zero
	constexpr double threshold = std::numeric_limits<double>::min(); // A very small nonzero number!
	return (std::abs(x - y) / std::max(threshold, min)) < tolerance;
}
