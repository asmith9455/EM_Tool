#pragma once

#include <math.h>
class EmWave
{
public:
	double sigma, epsR, muR, omega;
	const double pi = 3.14159265358979323846264338327950288;
	const double eps0 = 1e-9 / 36 / pi;
	const double mu0 = 4 * pi*1e-7;
	EmWave();
	~EmWave();

	double getAlpha();

	double getBeta();
};

