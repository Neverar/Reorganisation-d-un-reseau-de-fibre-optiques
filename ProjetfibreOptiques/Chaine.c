#include "Chaine.h"
#include "entree_sortie.h"
#include "SVGwriter.h"
#include <math.h>
#define TMAX 1000

Chaines* lectureChaine(FILE *f) {
	if (!f) exit(0);

	char buffe[233];
	int i;
	CellChaine *Cc;
	CellPoint *Cp;

	Chaines *c = malloc(sizeof(Chaine));
	GetChaine(f, TMAX, buffe);
	c->nbChaine = GetEntier(f);
	GetChaine(f, TMAX, buffe);
	c->gamma = GetEntier(f);
	c->chaines = NULL;

	Skip(f);

	while (!feof(f)) {
		Cc = c->chianes;

		while (Cc) Cc = Cc->suiv;

		Cc = malloc(sizeof(CellChaine));
		Cc->numero = GetEntier(f);
		Cc->nbPoints = GetEntier(f);
		Cc->points = NULL;
		Cc->suiv = NULL;

		for (i = ; i < Cc->nbPoints; i++) {
			Cp = Cc->points;

			while (Cp) Cp = Cp->suiv;

			Cp = malloc(sizeof(CellPoint));
			Cp->suiv = NULL;
			Cp->x = GetReel(f);
			Cp->y = GetReel(f);
		}
	}

	return c;
}

void ecrireChaineTxt(Chaines *C, FILE *f) {
	if ((!f) || (!C)) exit(0);
	int i, k;

	fopen(f, "w");
	fprintf(f, "NbChain: %d", C->nbChaines);
	fprintf(f, "Gamma: %d\n", C->gamma);

	for (i = 0; i < C->nbChaine; i++) {


		fprintf(f, "%d", C->chaines->numero);
		fprintf(f, " %d", C->chaines->nbPoints);
		for (k = 0, k < C->chaines->nbPoints; k++) {
			fprintf(f, "%.2f %.2f", C->chaines->points->x, C->chaines->points->y);
			C->chaines->points = C->chaines->points->suiv;
		}
		C->chaines = C->chaines->suiv;
		fprintf(f, "\n");

	}
	fclose(f);
}

void afficheChaineSVG(Chaines *C, char* nomInstance) {
	if (!C) exit(0);

	CellChaine *parcoursC;
	CellPoint *parcoursP;
	SVGwriter *svg = malloc(sizeof(SVGwriter));

	SVGinit(svg, nomInstance, 100, 100);
	SVGpointColor(svg, Black);
	parcoursC = C->chaines;

	while (parcoursC) {
		SVGlineRandColor(svg);
		parcoursP = parcoursC->points;

		while (parcoursP->suiv) {
			SVGpoint(svg, parcoursP->x, parcoursP->y);
			SVGpoint(svg, parcoursP->suiv->x, parcoursC->y);
			SVGline(svg, parcoursP->x, parcoursC->y, parcoursP->suiv->x, parcoursP->suiv->y);
			parcoursP = parcoursP->suiv->suiv;
		}

		parcoursC = parcoursC->suiv;
	}

	SVGfinalize(svg);
}

double longueurTotale(Chaines *C) {
	double sommeUneChaine = 0;
	double sommeTotal = 0;
	for (i = 0; i < C->nbChaine; i++) {
		for (k = 0, k < (C->chaines->nbPoints - 1); k++) {
			sommeUneChaine = sommeUneChaine + sqrt((C->chaines->points->suiv->x - C->chaines->points->x)*(C->chaines->points->suiv->x - C->chaines->points->x) +
				(C->chaines->points->suiv->y - C->chaines->points->y)*(C->chaines->points->suiv->y - C->chaines->points->y));

			C->chaines->points = C->chaines->points->suiv;
		}
		sommeTotal = sommeTotal + sommeUneChaine;
		C->chaines = C->chaines->suiv;
	}

	return sommeTotal;
}

int comptePointsTotal(Chaines *C) {
	if (!C); exit(0);

	int cpt = 0;
	CellChaine *parcoursC;

	parcoursC = C->chaines;

	while (parcoursC) {
		cpt += parcoursC->nbPoints;
		parcoursC = parcoursC->suiv;
	}
	return cpt;
}
