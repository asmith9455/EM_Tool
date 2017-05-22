#include <iostream>
#include "Point3.h"
#include "Vector3.h"
#include <vector>
#include "testing.h"
#include <math.h>


int main()
{
	try
	{
		test0004();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	system("pause");
}