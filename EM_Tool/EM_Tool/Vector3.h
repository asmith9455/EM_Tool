#pragma once
#include "Point3.h"
#include <math.h>
#include <iostream>

class Vector3
{
public:

	enum Type
	{
		RECTANGULAR_VECTOR,
		CYLINDRICAL_VECTOR,
		SPHERICAL_VECTOR
	};


	double components[3];
	Vector3::Type type;
	Point3 origin = Point3(0,0,0,Point3::Type::RECTANGULAR_POINT);

	Vector3(double _c1, double _c2, double _c3, Vector3::Type _type);
	Vector3(double _c1, double _c2, double _c3, Point3 _origin, Vector3::Type _type);

	void convertToRectangular();
	void convertToRectangular(Point3& p);
	void convertToCylindrical();
	void convertToCylindrical(Point3& p);
	//void convertToSpherical();
	//void convertToSpherical(Point3& p);
	double magnitude();
	double dot(Vector3&);
	Vector3 cross(Vector3&);
	double dotCast(Vector3&);
	char* getTypeString();

	friend std::ostream& operator<<(std::ostream& os, Vector3& v);

};

