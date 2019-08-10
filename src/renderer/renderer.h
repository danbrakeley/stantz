#pragma once

#include "camera.h"
#include "hitable.h"

namespace renderer {

struct config {
	int pixel_width;
	int pixel_height;
	int rays_per_pixel;
	int max_ray_depth;
	Camera* p_cam;
	Hitable* p_world;
};

void render(const config& cfg, int num_threads, short* p_frame);

} // namespace renderer
