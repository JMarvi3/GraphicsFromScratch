#include "sphere.h"

sphere::sphere(const vector &center, double radius, int color) : center(center), radius(radius), color(color) {};

std::string sphere::to_string() const
{
	return "{" + center.to_string() + ", " + std::to_string(radius) + ", " + std::to_string(color) + "}";
}

std::ostream& operator<<(std::ostream& os, const sphere& sphere)
{
	os << sphere.to_string();
	return os;
}
