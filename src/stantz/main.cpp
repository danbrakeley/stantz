#include "pch.h"
#include "renderer/camera.h"
#include "renderer/hitable.h"
#include "renderer/hitable_list.h"
#include "renderer/lambertian.h"
#include "renderer/metal.h"
#include "renderer/renderer.h"
#include "renderer/sphere.h"
#include "renderer/vec3.h"
#include <iostream>
#include <thread>
#include <assert.h>

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
