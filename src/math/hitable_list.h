#pragma once

#include "hitable.h"

class hitable_list : public hitable {
public:
	hitable_list() : m_list(nullptr), m_size(0) {}
	hitable_list(hitable** list, int size) : m_list(list), m_size(size) {}

	virtual bool hit(const ray& r, float t_min, float t_max, hit_record* p_rec) const override;

private:
	hitable** m_list;
	int m_size;
};
