#pragma once
#include "vector.h"
#include <iostream>
#include <sstream>

class sphere
{
public:
	vector center;
	double radius;
	int color;
	sphere(const vector &center, double radius, int color);
	std::string to_string() const;
	friend std::ostream& operator<<(std::ostream& os, const sphere& sphere);
};

