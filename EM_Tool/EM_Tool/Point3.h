#pragma once
#include <math.h>
#include <iostream>
#include <stdexcept>

class Point3
{
public:
	enum Type
	{
		RECTANGULAR_POINT,
		CYLINDRICAL_POINT,
		SPHERICAL_POINT
	};

	double pi = 3.14159265358979323846;
	double components[3];
	Point3::Type type;

	Point3(double _c1, double _c2, double _c3, Point3::Type _type);

	void convertToCylindrical();

	double getPhi();
	double getTheta();

	char* getTypeString();
	
	friend std::ostream& operator<<(std::ostream& os, Point3& v);
};