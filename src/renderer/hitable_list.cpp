#include "pch.h"
#include "hitable_list.h"
#include <assert.h>

bool HitableList::hit(const Ray& r, float t_min, float t_max, hit_record* p_rec) const {
	assert(p_rec != nullptr);

	hit_record temp_rec;
	bool hit_anything = false;
	float closest_so_far = t_max;
	for (int i = 0; i < m_size; i++) {
		if (m_list[i]->hit(r, t_min, closest_so_far, &temp_rec)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			*p_rec = temp_rec;
		}
	}
	return hit_anything;
}
