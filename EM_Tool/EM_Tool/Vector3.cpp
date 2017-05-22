#include "Vector3.h"

Vector3::Vector3(double _c1, double _c2, double _c3, Vector3::Type _type)
{
	components[0] = _c1;
	components[1] = _c2;
	components[2] = _c3;

	type = _type;
}

Vector3::Vector3(double _c1, double _c2, double _c3, Point3 _origin, Vector3::Type _type)
{
	components[0] = _c1;
	components[1] = _c2;
	components[2] = _c3;

	type = _type;
	origin = _origin;
}

void Vector3::convertToRectangular()
{
	if (type == Vector3::Type::CYLINDRICAL_VECTOR)
		convertToRectangular(origin);
	else if (type == Vector3::Type::SPHERICAL_VECTOR)
		convertToRectangular(origin);
}

void Vector3::convertToRectangular(Point3& p)
{
	if (type == Vector3::Type::CYLINDRICAL_VECTOR)
	{
		double A_x, A_y;
		double A_rho = components[0], A_phi = components[1];

		A_x = A_rho*cos(p.getPhi()) - A_phi*sin(p.getPhi());
		A_y = A_rho*sin(p.getPhi()) + A_phi*cos(p.getPhi());

		components[0] = A_x;
		components[1] = A_y;

		type = Vector3::Type::RECTANGULAR_VECTOR;
		origin = p;
	}
	else if (type == Vector3::Type::SPHERICAL_VECTOR)
	{
		double A_x, A_y, A_z;
		double A_r = components[0], A_theta = components[1], A_phi = components[2];

		A_x =
			A_r*sin(p.getTheta())*cos(p.getPhi()) +
			A_theta*cos(p.getTheta())*cos(p.getPhi()) -
			A_phi*sin(p.getTheta());

		A_y =
			A_r*sin(p.getTheta())*sin(p.getPhi()) +
			A_theta*cos(p.getTheta())*sin(p.getPhi()) -
			A_phi*cos(p.getTheta());

		A_z = A_r*cos(p.getTheta()) - A_theta*sin(p.getTheta());

		components[0] = A_x;
		components[1] = A_y;
		components[2] = A_z;

		type = Vector3::Type::RECTANGULAR_VECTOR;
	}
}

void Vector3::convertToCylindrical()
{
	if (type == Vector3::Type::RECTANGULAR_VECTOR)
		convertToCylindrical(origin);
	else if (type == Vector3::SPHERICAL_VECTOR)
		convertToCylindrical(origin);
}

void Vector3::convertToCylindrical(Point3& p)
{
	if (type == Vector3::Type::RECTANGULAR_VECTOR)
	{
		double A_rho, A_phi;
		double A_x = components[0], A_y = components[1];

		A_rho = A_x*cos(p.getPhi()) + A_y*sin(p.getPhi());
		A_phi = -A_x*sin(p.getPhi()) + A_y*cos(p.getPhi());

		components[0] = A_rho;
		components[1] = A_phi;

		type = Vector3::Type::CYLINDRICAL_VECTOR;
		origin = p;
	}
	if (type == Vector3::Type::SPHERICAL_VECTOR)
	{
		double A_rho, A_z;
		double A_r = components[0], A_theta = components[1];

		components[1] = components[2];
		A_rho = 
			A_r*sin(p.getTheta()) + 
			A_theta*cos(p.getTheta());
		A_z =
			A_r*cos(p.getTheta()) -
			A_theta*sin(p.getTheta());

		components[0] = A_rho;
		components[2] = A_z;
		type = Vector3::Type::CYLINDRICAL_VECTOR;
		origin = p;
	}
}

double Vector3::magnitude()
{
	return sqrt(components[0] * components[0] + components[1] * components[1] + components[2] * components[2]);
}

double Vector3::dot(Vector3& v)
{
	if (type==Vector3::Type::RECTANGULAR_VECTOR && v.type == Vector3::Type::RECTANGULAR_VECTOR)
		return components[0] * v.components[0] + components[1] * v.components[1] + components[2] * v.components[2];
	if (type == Vector3::Type::CYLINDRICAL_VECTOR && v.type == Vector3::Type::CYLINDRICAL_VECTOR)
	{
		double t11, t12, t21, t22;

		//just converts to rect and computes the dp there

		t11 = components[0] * cos(origin.getPhi()) - components[1] * sin(origin.getPhi());
		t12 = components[0] * sin(origin.getPhi()) + components[1] * cos(origin.getPhi());

		t21 = v.components[0] * cos(origin.getPhi()) - v.components[1] * sin(origin.getPhi());
		t22 = v.components[0] * sin(origin.getPhi()) + v.components[1] * cos(origin.getPhi());

		return t11*t21 + t12*t22 + components[2] * v.components[2];

		//The below code does the same thing as above, but I thought it would be helpful to have an explicit formula
		//for learning purposes.
		/*Vector3 vTmp1 = Vector3(
			components[0], 
			components[1], 
			components[2], 
			origin, 
			Vector3::Type::CYLINDRICAL_VECTOR);
		Vector3 vTmp2 = Vector3(
			v.components[0],
			v.components[1],
			v.components[2],
			v.origin,
			Vector3::Type::CYLINDRICAL_VECTOR);

		vTmp1.convertToRectangular();
		vTmp2.convertToRectangular();
		return vTmp1.dot(vTmp2);*/
	}
	
	throw std::runtime_error("Dot product not implemented for this type combination.");
}

Vector3 Vector3::cross(Vector3& v)
{
	return Vector3(
		components[1] * v.components[2] - components[2] * v.components[1],
		components[0] * v.components[2] - components[2] * v.components[0],
		components[0] * v.components[1] - components[1] * v.components[0],
		origin,
		type);
}

double Vector3::dotCast(Vector3& v)
{
	if (type == Vector3::Type::RECTANGULAR_VECTOR && v.type == Vector3::Type::RECTANGULAR_VECTOR)
		return components[0] * v.components[0] + components[1] * v.components[1] + components[2] * v.components[2];
	if (type == Vector3::Type::CYLINDRICAL_VECTOR && v.type == Vector3::Type::CYLINDRICAL_VECTOR)
	{
		/*double t11, t12, t21, t22;

		//just converts to rect and computes the dp there

		t11 = components[0] * cos(origin.getPhi()) - components[1] * sin(origin.getPhi());
		t12 = components[0] * sin(origin.getPhi()) + components[1] * cos(origin.getPhi());

		t21 = v.components[0] * cos(origin.getPhi()) - v.components[1] * sin(origin.getPhi());
		t22 = v.components[0] * sin(origin.getPhi()) + v.components[1] * cos(origin.getPhi());

		return t11*t21 + t12*t22 + components[2] * v.components[2];*/

		//The below code does the same thing as above, but I thought it would be helpful to have an explicit formula
		//for learning purposes.
		Vector3 vTmp1 = Vector3(
		components[0],
		components[1],
		components[2],
		origin,
		Vector3::Type::CYLINDRICAL_VECTOR);
		Vector3 vTmp2 = Vector3(
		v.components[0],
		v.components[1],
		v.components[2],
		v.origin,
		Vector3::Type::CYLINDRICAL_VECTOR);

		vTmp1.convertToRectangular();
		vTmp2.convertToRectangular();
		return vTmp1.dot(vTmp2);
	}

	throw std::runtime_error("Dot product not implemented for this type combination.");
}

char* Vector3::getTypeString() 
{
	if (type == Vector3::Type::RECTANGULAR_VECTOR)
		return "rec";

	if (type == Vector3::Type::CYLINDRICAL_VECTOR)
		return "cyl";

	if (type == Vector3::Type::SPHERICAL_VECTOR)
		return "sph";
}

std::ostream& operator<<(std::ostream& os, Vector3& v)
{
	os << "{ " << 
		v.components[0] << ", " << 
		v.components[1] << ", " << 
		v.components[2] << " } (" << 
		v.getTypeString() << ")";
	return os;
}