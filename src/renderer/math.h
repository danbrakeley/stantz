#pragma once

template<class T>
constexpr T pi() {
	return static_cast<T>(3.1415926535897932384626433832795028841971693993751);
}

template<class T>
inline const T deg_to_rad(T deg) {
	constexpr T ratio = pi<T>() / static_cast<T>(180);
	return deg * ratio;
}

template<class T>
inline const T rad_to_deg(T rad) {
	constexpr T ratio = static_cast<T>(180) / pi<T>();
	return rad * ratio;
}
