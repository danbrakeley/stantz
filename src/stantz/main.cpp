#include "pch.h"
#include "math/camera.h"
#include "math/hitable.h"
#include "math/hitable_list.h"
#include "math/lambertian.h"
#include "math/material.h"
#include "math/metal.h"
#include "math/rand.h"
#include "math/ray.h"
#include "math/sphere.h"
#include "math/vec3.h"
#include <iostream>
#include <limits>
#include <thread>
#include <assert.h>

const int kMaxDepth = 50;

Vec3 color(const Ray& r, const Hitable& world, int depth) {
	hit_record rec;
	// 0.001f here is to avoid "shadow acne", which is when hits that should be t=0 miss because of rounding error
	if (world.hit(r, 0.001f, std::numeric_limits<float>::max(), &rec)) {
		Ray scattered;
		Vec3 attenuation;
		if (depth < kMaxDepth) {
			assert(rec.p_mat != nullptr);
			if (rec.p_mat->scatter(r, rec, &attenuation, &scattered)) {
				return attenuation * color(scattered, world, depth + 1);
			}
		}
		return Vec3(0, 0, 0);
	}

	Vec3 unit_direction = r.direction().normalize();
	float t = 0.5f * (unit_direction.y() + 1.0f);
	return (1.0f - t) * Vec3(1, 1, 1) + t * Vec3(0.5f, 0.7f, 1);
}

constexpr int nx = 200;
constexpr int ny = 100;
constexpr int ns = 100;

void thread_tracer(const Hitable& world, const Camera& cam, int y_start, int y_stop, short* p_frame) {
	assert(p_frame != nullptr);
	int iframe = 0;
	for (int j = y_start; j >= y_stop; j--) {
		for (int i = 0; i < nx; i++) {
			Vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				float u = (float(i) + rand_unit<float>()) / float(nx);
				float v = (float(j) + rand_unit<float>()) / float(ny);
				Ray r = cam.get_ray(u, v);
				col += color(r, world, 0);
			}

			col /= float(ns);
			// gamma correction: raise each component to 1/2 power for gamma of 2
			col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			p_frame[iframe++] = short(255.99 * col.r());
			p_frame[iframe++] = short(255.99 * col.g());
			p_frame[iframe++] = short(255.99 * col.b());
		}
	}
	assert(iframe == 3 * (y_start - y_stop + 1) * nx);
	std::cerr << "Thread " << y_start << " did " << (y_start - y_stop + 1) << " lines." << std::endl;
}

int main() {
	Hitable* list[4];
	list[0] = new Sphere(Vec3(0, 0, -1), 0.5, new Lambertian(Vec3(0.8f, 0.3f, 0.3f)));
	list[1] = new Sphere(Vec3(0, -100.5f, -1), 100, new Lambertian(Vec3(0.8f, 0.8f, 0)));
	list[2] = new Sphere(Vec3(1, 0, -1), 0.5f, new Metal(Vec3(0.8f, 0.6f, 0.2f), 1));
	list[3] = new Sphere(Vec3(-1, 0, -1), 0.5f, new Metal(Vec3(0.8f, 0.8f, 0.8f), 0.3f));
	Hitable* world = new HitableList(list, 4);
	Camera cam;

	// frame buffer to collect work done by different threads
	int frame_size = nx * ny * 3;
	short* frame = new short[frame_size];

	// thread prep
	int thread_count = static_cast<int>(std::thread::hardware_concurrency());
	std::cerr << "Hardware Thread Count: " << thread_count << std::endl;
	int lines_per_thread = ny / thread_count;
	auto threads = new std::thread[thread_count];

	// run (thread_count - 1) threads
	int y_start = ny - 1;
	for (int i = 0; i < thread_count - 1; i++) {
		auto y_stop = y_start - lines_per_thread + 1;
		auto frame_with_offset = frame + (3 * i * lines_per_thread * nx);

		threads[i] = std::thread(thread_tracer, std::cref(*world), std::cref(cam), y_start, y_stop, frame_with_offset);
		y_start -= lines_per_thread;
	}

	// occupy the main thread with the remaining work
	thread_tracer(*world, cam, y_start, 0, frame + (3 * (thread_count - 1) * lines_per_thread * nx));

	// sync threads back to main
	for (int i = 0; i < thread_count - 1; i++) {
		threads[i].join();
	}

	// write ppm
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	int iframe = 0;
	for (int i = 0; i < nx * ny; i++) {
		std::cout << frame[iframe++] << " ";
		std::cout << frame[iframe++] << " ";
		std::cout << frame[iframe++];
		if ((i & 7) == 7) {
			std::cout << std::endl;
		} else {
			std::cout << " ";
		}
	}
	assert(iframe == frame_size);

	return 0;
}
