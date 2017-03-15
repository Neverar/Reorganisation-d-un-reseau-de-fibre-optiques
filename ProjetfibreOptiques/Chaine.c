#include "Chaine.h"
#include "entree_sortie.h"
#include "SVGwriter.h"
#include <math.h>
#include <stdlib.h>
#define TMAX 1000

Chaines* lectureChaine(FILE *f) {
	if (!f) exit(0);

	char buffe[233];
	int i;
	CellChaine *Cc;
	CellPoint *Cp;

	Chaines *c = malloc(sizeof(Chaines));
	GetChaine(f, TMAX, buffe);
	c->nbChaines = GetEntier(f);
	GetChaine(f, TMAX, buffe);
	c->gamma = GetEntier(f);
	c->chaines = NULL;

	Skip(f);

	while (!feof(f)) {
		Cc = c->chaines;

		while (Cc) Cc = Cc->suiv;

		Cc = malloc(sizeof(CellChaine));
		Cc->numero = GetEntier(f);
		Cc->nbPoints = GetEntier(f);
		Cc->points = NULL;
		Cc->suiv = NULL;

		for (i = 0 ; i < Cc->nbPoints; i++) {
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

/* faut modifier cette fonction a Kamil */
void ecrireChaineTxt(Chaines *C, FILE *f) {
	if ((!f) || (!C)) exit(0);
	int i, k;

	fprintf(f, "NbChain: %d", C->nbChaines);
	fprintf(f, "Gamma: %d\n", C->gamma);

	for (i = 0; i < C->nbChaines; i++) {
		fprintf(f, "%d", C->chaines->numero);
		fprintf(f, " %d", C->chaines->nbPoints);
		
		for (k = 0; k < C->chaines->nbPoints; k++) {
			fprintf(f, "%.2f %.2f", C->chaines->points->x, C->chaines->points->y);
			C->chaines->points = C->chaines->points->suiv;     /* ne faut pas se effectuer sur lui-meme, sinon ce pointeur va chager. Dois creer un parcours pour imcrementer la liste */
		}
		
		C->chaines = C->chaines->suiv;             /* Pareil de ce dessus */
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
			SVGpoint(svg, parcoursP->suiv->x, parcoursP->suiv->y);
			SVGline(svg, parcoursP->x, parcoursP->y, parcoursP->suiv->x, parcoursP->suiv->y);
			parcoursP = parcoursP->suiv->suiv;
		}

		parcoursC = parcoursC->suiv;
	}

	SVGfinalize(svg);
}

/* faut modifier cette fonction aussi a kamil */
double longueurTotale(Chaines *C) {
	int i, k;
	double sommeUneChaine = 0;
	double sommeTotal = 0;
	for (i = 0; i < C->nbChaines; i++) {
		for (k = 0; k < (C->chaines->nbPoints - 1); k++) {
			/* Essais a diminuer la longuer de ce qui dans les parentheses de sqrt, sinon je sais pas pourquoi la compation va rendre une eurrer*/
			/*Ou bien tu peux creer un variable pour stocker la valeur dans la parenthese */
		
			sommeUneChaine = sommeUneChaine + sqrt((C->chaines->points->suiv->x - C->chaines->points->x)*(C->chaines->points->suiv->x - C->chaines->points->x) +
				(C->chaines->points->suiv->y - C->chaines->points->y)*(C->chaines->points->suiv->y - C->chaines->points->y));  

			C->chaines->points = C->chaines->points->suiv; /* Pareil, faut creer un parcours */
		}
		sommeTotal = sommeTotal + sommeUneChaine;
		C->chaines = C->chaines->suiv; /* faut creer un parcours */                                    
	}

	return sommeTotal;
}

int comptePointsTotal(Chaines *C) {
	if (!C) exit(0);

	int cpt = 0;
	CellChaine *parcoursC;

	parcoursC = C->chaines;

	while (parcoursC) {
		cpt += parcoursC->nbPoints;
		parcoursC = parcoursC->suiv;
	}
	return cpt;
}
