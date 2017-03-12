#ifndef __STRUCTHACHAGE_H__
#define __STRUCTHACHAGE_H__

#include "Reseau.h"

typedef struct {
	int nbE;
	int m;
	CellNoeud **liste;
}TableHachage;

double clef(double x, double y);
int fonctionHachage(double k);
#endif