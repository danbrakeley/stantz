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

Vec3 color(const Ray& r, const Hitable& world, int max_depth, int cur_depth) {
	hit_record rec;
	// 0.001f here is to avoid "shadow acne", which is when hits that should be t=0 miss because of rounding error
	if (world.hit(r, 0.001f, std::numeric_limits<float>::max(), &rec)) {
		Ray scattered;
		Vec3 attenuation;
		if (cur_depth < max_depth) {
			assert(rec.p_mat != nullptr);
			if (rec.p_mat->scatter(r, rec, &attenuation, &scattered)) {
				return attenuation * color(scattered, world, max_depth, cur_depth + 1);
			}
		}
		return Vec3(0, 0, 0);
	}

	Vec3 unit_direction = r.direction().normalize();
	float t = 0.5f * (unit_direction.y() + 1.0f);
	return (1.0f - t) * Vec3(1, 1, 1) + t * Vec3(0.5f, 0.7f, 1);
}

namespace renderer {

struct config {
	int pixel_width;
	int pixel_height;
	int rays_per_pixel;
	int max_ray_depth;
	Camera cam;
	Hitable* p_world;
};

void thread_tracer(const config& cfg, int y_start, int y_stop, short* p_frame) {
	assert(p_frame != nullptr);
	int iframe = 0;
	for (int j = y_start; j >= y_stop; j--) {
		for (int i = 0; i < cfg.pixel_width; i++) {
			Vec3 col(0, 0, 0);
			for (int s = 0; s < cfg.rays_per_pixel; s++) {
				float u = (float(i) + rand_unit<float>()) / float(cfg.pixel_width);
				float v = (float(j) + rand_unit<float>()) / float(cfg.pixel_height);
				Ray r = cfg.cam.get_ray(u, v);
				col += color(r, *cfg.p_world, cfg.max_ray_depth, 0);
			}

			col /= float(cfg.rays_per_pixel);
			// gamma correction: raise each component to 1/2 power for gamma of 2
			col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			p_frame[iframe++] = short(255.99 * col.r());
			p_frame[iframe++] = short(255.99 * col.g());
			p_frame[iframe++] = short(255.99 * col.b());
		}
	}
	assert(iframe == 3 * (y_start - y_stop + 1) * cfg.pixel_width);
	std::cerr << "Thread " << y_start << " did " << (y_start - y_stop + 1) << " lines." << std::endl;
}

void render(const config& cfg, int num_threads, short* p_frame) {
	std::cerr << "Total Threads: " << num_threads << std::endl;
	int lines_per_thread = cfg.pixel_height / num_threads;
	auto threads = new std::thread[num_threads - 1];

	// run (num_threads - 1) threads
	int y_start = cfg.pixel_height - 1;
	for (int i = 0; i < num_threads - 1; i++) {
		auto y_stop = y_start - lines_per_thread + 1;
		auto frame_with_offset = p_frame + (3 * i * lines_per_thread * cfg.pixel_width);

		threads[i] = std::thread(thread_tracer, std::cref(cfg), y_start, y_stop, frame_with_offset);
		y_start -= lines_per_thread;
	}

	// occupy the main thread with the remaining work
	thread_tracer(cfg, y_start, 0, p_frame + (3 * (num_threads - 1) * lines_per_thread * cfg.pixel_width));

	// sync threads back to main
	for (int i = 0; i < num_threads - 1; i++) {
		threads[i].join();
	}
}

} // namespace renderer

int main() {
	renderer::config cfg = {};
	cfg.pixel_width = 200;
	cfg.pixel_height = 100;
	cfg.rays_per_pixel = 100;
	cfg.max_ray_depth = 50;
	cfg.cam = Camera();

	Hitable* list[4];
	list[0] = new Sphere(Vec3(0, 0, -1), 0.5, new Lambertian(Vec3(0.8f, 0.3f, 0.3f)));
	list[1] = new Sphere(Vec3(0, -100.5f, -1), 100, new Lambertian(Vec3(0.8f, 0.8f, 0)));
	list[2] = new Sphere(Vec3(1, 0, -1), 0.5f, new Metal(Vec3(0.8f, 0.6f, 0.2f), 1));
	list[3] = new Sphere(Vec3(-1, 0, -1), 0.5f, new Metal(Vec3(0.8f, 0.8f, 0.8f), 0.3f));
	cfg.p_world = new HitableList(list, 4);

	// frame buffer to collect work done by different threads
	int frame_size = cfg.pixel_width * cfg.pixel_height * 3;
	short* frame = new short[frame_size];

	// render
	int num_threads = static_cast<int>(std::thread::hardware_concurrency());
	renderer::render(cfg, num_threads, frame);

	// write ppm
	std::cout << "P3\n" << cfg.pixel_width << " " << cfg.pixel_height << "\n255\n";
	int iframe = 0;
	for (int i = 0; i < cfg.pixel_width * cfg.pixel_height; i++) {
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
