#include <iostream>
#include "Point3.h"
#include "Vector3.h"
#include <vector>
#include "testing.h"
#include <math.h>
#include "EmWave.h"

int main()
{
	try
	{
		EmWave wave1;
		wave1.sigma = 4.0;
		wave1.epsR = 81;
		wave1.muR = 1;
		wave1.omega = 2*wave1.pi*1e2;
		std::cout << "alpha: " << wave1.getAlpha() << std::endl;
		std::cout << "beta: " << wave1.getBeta() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	system("pause");
}