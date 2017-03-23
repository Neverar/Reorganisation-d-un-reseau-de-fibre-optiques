#include "Hachage.h"
#include <math.h>
#include <stdio.h>

double clef(double x, double y)
{
	return (y + (x + y) * (x + y + 1) / 2);
}

long fonctionHachage(double k, int M)
{
	double A = (sqrt(5) - 1) / 2;
	return (long)(M * ((k * A) - (long)(k * A)));
}
