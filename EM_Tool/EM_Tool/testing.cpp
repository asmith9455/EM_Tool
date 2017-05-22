#include "testing.h"


void convertGridToCylindrical(Vector3 rectVect, std::vector<double> Xs, std::vector<double> Ys)
{
	for (unsigned int i = 0; i < Xs.size(); i++)
	{
		for (unsigned int j = 0; j < Ys.size(); j++)
		{
			Point3 pTmp(Xs[i], Ys[j], 0, Point3::Type::RECTANGULAR_POINT);

			Vector3 vTmp(
				rectVect.components[0],
				rectVect.components[1],
				rectVect.components[2],
				Vector3::Type::RECTANGULAR_VECTOR);

			std::cout << "Point : " << pTmp << std::endl;
			std::cout << "Vector: " << vTmp << std::endl;
			vTmp.convertToCylindrical(pTmp);
			std::cout << "Vector: " << vTmp << std::endl;
			std::cout << std::endl;
		}
	}
}

void testGridToCylindrical()
{
	std::vector<double> xValues = { 0,1,2,3 };
	std::vector<double> yValues = { 0,1,2,3 };

	Vector3 v1(3, 4, 0, Vector3::Type::RECTANGULAR_VECTOR);


	convertGridToCylindrical(v1, xValues, yValues);
}

void testMathStackExchangeProblem205298()
{
	//https://math.stackexchange.com/questions/205298/cartesian-vector-to-cylindrical-components
	Vector3 v1(-4, -6, 9, Vector3::Type::RECTANGULAR_VECTOR);
	Point3 p1(3, 2, -7, Point3::Type::RECTANGULAR_POINT);

	v1.convertToCylindrical(p1);

	std::cout << "Ans: " << v1 << std::endl;
}

void test0000()
{
	//This test shows that a cylindrical vector equivalent to a rectangular vector 
	//has different components depending on its origin (the point at which it starts).
	//This test also shows that the length of a vector expressed in the cylindrical 
	//coordinate system is independent of its point of origin, and in each case matches
	//the magnitude of the rectangular vector from which it was derived.

	Vector3 v1(6, 1, 0, Vector3::Type::RECTANGULAR_VECTOR);
	Vector3 v2(6, 1, 0, Vector3::Type::RECTANGULAR_VECTOR);
	Vector3 v3(6, 1, 0, Vector3::Type::RECTANGULAR_VECTOR);

	Point3 p1(1, 2, 3, Point3::Type::RECTANGULAR_POINT);
	Point3 p2(2, -4, 5, Point3::Type::RECTANGULAR_POINT);

	double mag1 = v1.magnitude();
	v2.convertToCylindrical(p1);
	double mag2 = v2.magnitude();
	v3.convertToCylindrical(p2);
	double mag3 = v3.magnitude();

	//note that there is some rounding error imposed by using doubles, so compare to 10 decimal places.
	bool equal = abs(mag2 - mag1) < 1e-10 && abs(mag2 - mag3) < 1e-10;

	//The important conclusion is that any variable (ex phi, theta) in the matrices that transform
	//vector fields between coordinate systems is unique for each point at which the vector is evaluated.
	//For example it doesn't make sense for the rectangular vector (2,3,4) to be converted into a cylindrical
	//vector that does not vary with its origin - to evaluate the cylindrical vector into constant components
	//requires a point of origin to be specified.
}

void test0001()
{
	//this test shows that ay (rec) = ap (cyl) when phi = pi/2 
	double pi = 3.14159265358979323846;

	Vector3 v(0, 1, 0, Vector3::RECTANGULAR_VECTOR);
	Point3 p(5, pi / 2, 3, Point3::CYLINDRICAL_POINT);

	v.convertToCylindrical(p);

	std::cout << v << std::endl;

	//therefore ay = arho when phi = pi/2 in cyl
}

void test0002()
{
	//this test explores dot product behaviour in rec and cyl
	double pi = 3.14159265358979323846;
	Vector3 v1(2, 6, -7, Vector3::RECTANGULAR_VECTOR);
	Vector3 v2(3, 4, 5, Vector3::RECTANGULAR_VECTOR);

	double dp_rec = v1.dot(v2);

	Point3 p(5,pi/3, 3, Point3::CYLINDRICAL_POINT);
	v1.convertToCylindrical(p);
	v2.convertToCylindrical(p);

	double dp_cyl = v1.dot(v2);

	v1.convertToRectangular();
	v2.convertToRectangular();

	double dp_rec_agian = v1.dot(v2);

	std::cout << "Rec DP  = " << dp_rec << " and Cyl DP = " << dp_cyl << std::endl;
	std::cout << "Rec DP Again  = " << dp_rec_agian << std::endl;
}

/*void test0003()
{
	//this test explores dot product behaviour in rec and cyl
	double pi = 3.14159265358979323846;
	Vector3 v1(2, 6, -7, Vector3::RECTANGULAR_VECTOR);
	Vector3 v2(3, 4, 5, Vector3::RECTANGULAR_VECTOR);


	Point3 p(5, pi / 3, 3, Point3::CYLINDRICAL_POINT);
	v1.convertToCylindrical(p);
	v2.convertToCylindrical(p);

	int n = 100000;
	
	for(int i = 0; i < n; i++)
		double dp_cyl = v1.dot(v2);

	for (int i = 0; i < n; i++)
		double dp_rec_agian = v1.dotCast(v2);

}*/

void test0004()
{
	//this test explores dot product behaviour in rec and cyl
	double pi = 3.14159265358979323846;

	Point3 p(1, pi / 3, 0, Point3::CYLINDRICAL_POINT);

	Vector3 a_theta(0, 1, 0, p, Vector3::SPHERICAL_VECTOR);
	Vector3 H(0, 0.067667642, 1, p,  Vector3::CYLINDRICAL_VECTOR);

	std::cout << "point is: " << p << std::endl;
	std::cout << "a_theta is: " << a_theta <<std::endl;
	a_theta.convertToCylindrical();
	std::cout << "a_theta is: " << a_theta << std::endl;
	std::cout << "H is: " << H << std::endl;
	std::cout << "H x a_theta is: " << H.cross(a_theta) << std::endl;
}

void test0005()
{
	double pi = 3.14159265358979323846;
	Point3 p1(0, 0, 3, Point3::RECTANGULAR_POINT);
	Point3 p2(10, -2, 3, Point3::RECTANGULAR_POINT);

	Vector3 v1(3, 2, 7, p1, Vector3::CYLINDRICAL_VECTOR);
	Vector3 v2(3, 2, 7, p2, Vector3::CYLINDRICAL_VECTOR);
	Vector3 az(0, 0, 1, Vector3::RECTANGULAR_VECTOR);

	v1.convertToRectangular();
	v2.convertToRectangular();

	std::cout << 90 - 180.0 / pi*v1.dot(az) / v1.magnitude() << std::endl;
	std::cout << 90 - 180.0 / pi*v2.dot(az) / v2.magnitude() << std::endl;
}

void test0006()
{
	double pi = 3.14159265358979323846;
	Point3 p1(0, 0, 3, Point3::RECTANGULAR_POINT);
	Point3 p2(10, -2, 3, Point3::RECTANGULAR_POINT);

	Vector3 v1(3, 2, 7, p1, Vector3::CYLINDRICAL_VECTOR);
	Vector3 v2(3, 2, 7, p2, Vector3::CYLINDRICAL_VECTOR);
	Vector3 az(0, 0, 1, Vector3::RECTANGULAR_VECTOR);

	v1.convertToRectangular();
	v2.convertToRectangular();

	std::cout << 90 - 180.0 / pi*v1.dot(az) / v1.magnitude() << std::endl;
	std::cout << 90 - 180.0 / pi*v2.dot(az) / v2.magnitude() << std::endl;
}