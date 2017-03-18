#include "Chaine.h"
#include "entree_sortie.h"
#include "SVGwriter.h"
#include <math.h>
#include <stdlib.h>
#define TMAX 1000

Chaines* lectureChaine(FILE *f) {
	if (!f) exit(0);

	char buffe[233];
	int i = 0, j;
	CellChaine *Cc;
	CellPoint *Cp;

	Chaines *c = malloc(sizeof(Chaines));
	if(!c) {
		printf("echec d'alloer mermoires\n ");
		exit(0);
	}
	GetChaine(f, TMAX, buffe);
	c->nbChaines = GetEntier(f);
	GetChaine(f, TMAX, buffe);
	c->gamma = GetEntier(f);
	c->chaines = NULL;

	while (i != c->nbChaines) {

		Cc = malloc(sizeof(CellChaine));
		Cc->numero = GetEntier(f);
		Cc->nbPoints = GetEntier(f);

		Cc->points = NULL;
		Cc->suiv = NULL;
		
		for (j = 0 ; j < Cc->nbPoints; j++) {
			Cp = malloc(sizeof(CellPoint));
			Cp->suiv = NULL;
			Cp->x = GetReel(f);
			Cp->y = GetReel(f);

			Cc->points = AjouterTetePoint(Cc->points, Cp);
		}

		c->chaines = AjouterTeteChaine(c->chaines, Cc);
		i++;
	}	

	return c;
}

void ecrireChaineTxt(Chaines *C, FILE *f) {
	if ((!f) || (!C)) exit(0);
	int i, k;

	fprintf(f, "NbChain: %d\n", C->nbChaines);
	fprintf(f, "Gamma: %d\n\n", C->gamma);
	fprintf(stdout, "NbChain: %d\n", C->nbChaines);
	fprintf(stdout, "Gamma: %d\n\n", C->gamma);



	for (i = 0; i < C->nbChaines; i++) {
		fprintf(f, "%d", C->chaines->numero);
		fprintf(stdout, "%d", C->chaines->numero);
		fprintf(f, " %d", C->chaines->nbPoints);
		fprintf(stdout, " %d", C->chaines->nbPoints);
		
		for (k = 0; k < C->chaines->nbPoints; k++) {
			fprintf(f, " %.2f %.2f", C->chaines->points->x, C->chaines->points->y);
			fprintf(stdout, " %.2f %.2f", C->chaines->points->x, C->chaines->points->y);
			C->chaines->points = C->chaines->points->suiv;     
		}
		
		C->chaines = C->chaines->suiv;             
		fprintf(f, "\n");
		fprintf(stdout, "\n");
	}
	
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

		while (parcoursP->suiv->suiv) {
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

CellPoint* AjouterTetePoint(CellPoint* p, CellPoint* Nouv)
{
	Nouv->suiv = p;
	return Nouv;
}

CellChaine* AjouterTeteChaine(CellChaine* c, CellChaine* Nouv)
{
	Nouv->suiv = c;
	return Nouv;
}