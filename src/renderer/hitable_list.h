#pragma once

#include "hitable.h"

class HitableList : public Hitable {
public:
	HitableList() : m_list(nullptr), m_size(0) {}
	HitableList(Hitable** list, int size) : m_list(list), m_size(size) {}

	virtual bool hit(const Ray& r, float t_min, float t_max, hit_record* p_rec) const override;

private:
	Hitable** m_list;
	int m_size;
};
