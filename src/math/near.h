#pragma once

// from https://www.reidatcheson.com/floating%20point/comparison/2019/03/20/floating-point-comparison.html

bool almost_equal(float x, float y, float tolerance, float zero_tolerance);
bool almost_equal(double x, double y, double tolerance, double zero_tolerance);
