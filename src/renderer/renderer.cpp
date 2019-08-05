#pragma once

#include "pch.h"
#include "renderer.h"
#include "material.h"
#include "rand.h"
#include "vec3.h"
#include <iostream>
#include <limits>
#include <thread>
#include <assert.h>

namespace renderer {

Vec3 color(const Ray& r, const Hitable& world, int max_depth, int cur_depth) {
	hit_record rec;
	// 0.001f here is to avoid "shadow acne", which is rounding error at t=0
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
	auto threads = new std::thread[num_threads];

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
