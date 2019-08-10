#include "pch.h"
#include "renderer/camera.h"
#include "renderer/dielectric.h"
#include "renderer/hitable.h"
#include "renderer/hitable_list.h"
#include "renderer/lambertian.h"
#include "renderer/metal.h"
#include "renderer/rand.h"
#include "renderer/renderer.h"
#include "renderer/sphere.h"
#include "renderer/vec3.h"
#include <iostream>
#include <thread>
#include <assert.h>

Hitable* random_scene() {
	Hitable** list = new Hitable*[501];
	list[0] = new Sphere(Vec3(0, -1000, 0), 1000, new Lambertian(Vec3(0.5f, 0.5f, 0.5f)));
	int i = 1;
	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			float choose_mat = rand_unit<float>();
			Vec3 center(a + 0.9f * rand_unit<float>(), 0.2f, b + 0.9f * rand_unit<float>());
			if ((center - Vec3(4, 0.2f, 0)).length() > 0.9f) {
				if (choose_mat < 0.8f) {
					// diffuse
					list[i++] = new Sphere(
					  center, 0.2f, new Lambertian(Vec3(rand_unit_x2<float>(), rand_unit_x2<float>(), rand_unit_x2<float>())));
				} else if (choose_mat < 0.95f) {
					// metal
					list[i++] = new Sphere(
					  center,
					  0.2f,
					  new Metal(
					    Vec3(0.5f * (1 + rand_unit<float>()), 0.5f * (1 + rand_unit<float>()), 0.5f * (1 + rand_unit<float>())),
					    0.5f * rand_unit<float>()));
				} else {
					// glass
					list[i++] = new Sphere(center, 0.2f, new Dielectric(1.5f));
				}
			}
		}
	}

	list[i++] = new Sphere(Vec3(0, 1, 0), 1, new Dielectric(1.5f));
	list[i++] = new Sphere(Vec3(-4, 1, 0), 1, new Lambertian(Vec3(0.4f, 0.2f, 0.1f)));
	list[i++] = new Sphere(Vec3(4, 1, 0), 1, new Metal(Vec3(0.7f, 0.6f, 0.5f), 0));

	return new HitableList(list, i);
}

int main() {
	renderer::config cfg = {};
	cfg.pixel_width = 1600;
	cfg.pixel_height = 900;
	cfg.rays_per_pixel = 500;
	cfg.max_ray_depth = 50;
	float aspect = static_cast<float>(cfg.pixel_width) / static_cast<float>(cfg.pixel_height);

	Vec3 lookfrom(12, 2, 4);
	Vec3 lookat(0, 0, -1);
	float dist_to_focus = (lookfrom - lookat).length();
	float aperture = 0.1f;
	cfg.p_cam = new DofCamera(lookfrom, lookat, Vec3(0, 1, 0), 20, aspect, aperture, dist_to_focus);

	// Hitable* list[5];
	// list[0] = new Sphere(Vec3(0, 0, -1), 0.5, new Lambertian(Vec3(0.1f, 0.2f, 0.5f)));
	// list[1] = new Sphere(Vec3(0, -100.5f, -1), 100, new Lambertian(Vec3(0.8f, 0.8f, 0)));
	// list[2] = new Sphere(Vec3(1, 0, -1), 0.5f, new Metal(Vec3(0.8f, 0.6f, 0.2f), 0.2f));
	// list[3] = new Sphere(Vec3(-1, 0, -1), 0.5f, new Dielectric(1.5f));
	// list[4] = new Sphere(Vec3(-1, 0, -1), -0.45f, new Dielectric(1.5f));
	// cfg.p_world = new HitableList(list, 5);
	cfg.p_world = random_scene();

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

	delete frame;
	assert(iframe == frame_size);

	return 0;
}
