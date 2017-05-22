#include "Point3.h"


Point3::Point3(double _c1, double _c2, double _c3, Point3::Type _type)
{
	components[0] = _c1;
	components[1] = _c2;
	components[2] = _c3;

	type = _type;
}

double Point3::getPhi()
{
	if (type == Point3::Type::RECTANGULAR_POINT)
		return atan2(components[1], components[0]);

	if (type == Point3::Type::CYLINDRICAL_POINT)
		return components[1];

	if (type == Point3::Type::SPHERICAL_POINT)
		return components[2];

	throw std::runtime_error("Not yet implemented.");
}

double Point3::getTheta()
{
	if (type == Point3::Type::RECTANGULAR_POINT)
		return atan2(components[2], sqrt(components[0]*components[0] + components[1]*components[1]));
	if (type == Point3::Type::SPHERICAL_POINT)
		return components[1];
	if (type == Point3::Type::CYLINDRICAL_POINT)
		return pi/2.0-atan2(components[2],components[0]);


	throw std::runtime_error("Not yet implemented.");
}

void Point3::convertToCylindrical()
{
	if (type == Point3::Type::RECTANGULAR_POINT)
	{
		double rho, phi;

		rho = sqrt(components[0] * components[0] + components[1] * components[1]);
		phi = atan2(components[1], components[0]);

		components[0] = rho;
		components[1] = phi;

		type = Point3::Type::CYLINDRICAL_POINT;
	}
	if (type == Point3::Type::SPHERICAL_POINT)
	{
		throw std::runtime_error("Not yet implemented.");
	}
}

char* Point3::getTypeString()
{
	if (type == Point3::Type::RECTANGULAR_POINT)
		return "rec";

	if (type == Point3::Type::CYLINDRICAL_POINT)
		return "cyl";

	if (type == Point3::Type::SPHERICAL_POINT)
		return "sph";
}

std::ostream& operator<<(std::ostream& os, Point3& v)
{
	os << "{ " << 
		v.components[0] << ", " << 
		v.components[1] << ", " << 
		v.components[2] << " } (" << 
		v.getTypeString() << ")";
	return os;
}