#include "pch.h"
#include "math/hitable.h"
#include "math/hitable_list.h"
#include "math/ray.h"
#include "math/sphere.h"
#include "math/vec3.h"
#include <limits>

vec3 color(const ray& r, hitable* world) {
	hit_record rec;
	if (world->hit(r, 0, std::numeric_limits<float>::max(), &rec)) {
		return 0.5 * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
	}

	vec3 unit_direction = r.direction().normalize();
	float t = 0.5f * (unit_direction.y() + 1.0f);
	return (1.0f - t) * vec3(1, 1, 1) + t * vec3(0.5f, 0.7f, 1);
}

int main() {
	int nx = 200;
	int ny = 100;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	vec3 lower_left(-2, -1, -1);
	vec3 horiz(4, 0, 0);
	vec3 vert(0, 2, 0);
	vec3 origin(0, 0, 0);

	hitable* list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5f, -1), 100);
	hitable* world = new hitable_list(list, 2);

	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			ray r(origin, lower_left + u * horiz + v * vert);

			vec3 p = r.point(2);
			vec3 col = color(r, world);

			int ir = int(255.99 * col.r());
			int ig = int(255.99 * col.g());
			int ib = int(255.99 * col.b());

			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}

	return 0;
}
