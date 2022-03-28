#include "vector.h"

vector::vector() = default;

vector::vector(double init_x, double init_y, double init_z) : x(init_x), y(init_y), z(init_z) {}

double vector::dot(const vector& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

double vector::length() const
{
	return sqrt(x*x + y*y + z*z);
}

std::string vector::to_string() const
{
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}

vector operator-(const vector &lhs, const vector& rhs)
{
	return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
}

vector operator+(const vector& lhs, const vector& rhs)
{
	return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
}

std::ostream& operator<<(std::ostream& os, const vector& vector)
{
	os << vector.to_string();
	return os;
}

vector operator/(const vector& left, const double right)
{
	return {left.x / right, left.y / right, left.z / right};
}

vector operator*(const vector& left, const double right)
{
	return { left.x * right, left.y * right, left.z * right };
}
