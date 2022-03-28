#pragma once
#include <string>
#include <iostream>
#include <sstream>

class vector
{
	double x = 0, y = 0, z = 0;
public:
	vector();
	vector(double x, double y, double z);
	double dot(const vector& other) const;
	double length() const;
	friend vector operator-(const vector &lhs, const vector& rhs);
	friend vector operator+(const vector& lhs, const vector& rhs);
	std::string to_string() const;
	friend std::ostream& operator<<(std::ostream& os, const vector& vector);
	friend vector operator/(const vector& left, const double right);
	friend vector operator*(const vector& left, const double right);
};

