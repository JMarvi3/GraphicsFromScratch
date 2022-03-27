#pragma once
#include "vector.h"

class light
{
	double intensity;
public:
	double get_intensity() const { return intensity; }
	light(double init_intensity) : intensity(init_intensity) {}
	virtual ~light() = default;
};

class ambient_light : public light
{
public:
	ambient_light(double init_intensity) : light(init_intensity) {}
};

class point_light : public light
{
	vector position;
public:
	vector get_position() const { return position; }
	point_light(double init_intensity, vector init_position) : light(init_intensity), position(init_position) {}
};

class directional_light : public light
{
	vector direction;
public:
	vector get_direction() const { return direction; }
	directional_light(double init_intensity, vector init_direction) : light(init_intensity), direction(init_direction) {}
};

