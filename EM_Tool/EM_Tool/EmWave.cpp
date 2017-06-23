#include "EmWave.h"



EmWave::EmWave()
{
}


EmWave::~EmWave()
{
}

double EmWave::getAlpha()
{
	return omega*
		sqrt(
			muR*mu0*epsR*eps0 / 2.0 * 
			(
				sqrt(
					1.0 + (sigma / omega / epsR/eps0)*(sigma / omega / epsR/eps0)
				) 
				- 1.0
			)
		);
}

double EmWave::getBeta()
{
	return omega*sqrt(muR*mu0*epsR*eps0 / 2.0 * (sqrt(1.0 + (sigma / omega / epsR / eps0)*(sigma / omega / epsR / eps0)) + 1.0));
}
