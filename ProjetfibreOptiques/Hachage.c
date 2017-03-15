#include "Hachage.h"
#include <math.h>

double clef(double x, double y) {
	return (y + (x + y)*(x + y + 1) / 2);
}

int fonctionHachage(double k, int M) {
	double A = (sqrt(5) - 1) / 2;

	return (int)(M*(k*A - (int)(k*A)));
}