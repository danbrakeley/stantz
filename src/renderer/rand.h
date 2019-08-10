#pragma once

#include <random>

// generated numbers are in [0, 1)
template<class T>
T rand_unit() {
	static thread_local std::mt19937 generator;
	std::uniform_real_distribution<T> distribution(0, 1);
	return distribution(generator);
}

template<class T>
inline T rand_unit_x2() {
	return rand_unit<T>() * rand_unit<T>();
}
