#pragma once

#include "pch.h"
#include "renderer.h"
#include "material.h"
#include "rand.h"
#include "vec3.h"
#include <iostream>
#include <limits>
#include <mutex>
#include <thread>
#include <assert.h>

namespace renderer {

// this manages handing out lines in need of rendering to available threads
class LineWrangler {
public:
	LineWrangler(int num_lines) : num_lines_(num_lines) {}

	int next_line() {
		std::lock_guard<std::mutex> lockGuard(mutex_);
		if (num_lines_ <= 0) {
			return -1;
		}
		return --num_lines_;
	}

	void report_complete(int lines) {
		std::lock_guard<std::mutex> lockGuard(mutex_cerr_);
		std::cerr << "Thread " << std::this_thread::get_id() << " finished " << lines << " line(s)." << std::endl;
	}

private:
	int num_lines_;
	std::mutex mutex_;
	std::mutex mutex_cerr_;
};

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

void thread_tracer(const config& cfg, LineWrangler* p_liner, short* p_frame) {
	assert(p_frame != nullptr);
	assert(p_liner != nullptr);

	int count = 0;
	for (;;) {
		int line = p_liner->next_line();
		if (line == -1) {
			p_liner->report_complete(count);
			return;
		}
		++count;

		int iframe = (cfg.pixel_height - (line + 1)) * cfg.pixel_width * 3;
		for (int i = 0; i < cfg.pixel_width; i++) {
			Vec3 col(0, 0, 0);
			for (int s = 0; s < cfg.rays_per_pixel; s++) {
				float u = (float(i) + rand_unit<float>()) / float(cfg.pixel_width);
				float v = (float(line) + rand_unit<float>()) / float(cfg.pixel_height);
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
}

void render(const config& cfg, int num_threads, short* p_frame) {
	std::cerr << "Total Threads: " << num_threads << std::endl;
	auto threads = new std::thread[num_threads];

	LineWrangler liner(cfg.pixel_height);
	for (int i = 0; i < num_threads; i++) {
		threads[i] = std::thread(thread_tracer, std::cref(cfg), &liner, p_frame);
	}

	// sync threads back to main
	for (int i = 0; i < num_threads - 1; i++) {
		threads[i].join();
	}
}

} // namespace renderer
