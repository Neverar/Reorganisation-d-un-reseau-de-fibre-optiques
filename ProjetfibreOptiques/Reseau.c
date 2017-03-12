#include<stdlib.h>
#include<stdio.h>
#include "Reseau.h"

#define M 1000

Noeud* rechercherCreeNoeudListe(Reseau *R, double x, double y) {
	if (!R) exit(0);

	CellNoeud *parcoursN, *Nn;
	parcoursN = R->noeuds;

	while (parcoursN) {
		if ((parcoursN->nd->x == x) && (parcoursN->nd->y == y))
			return parcoursN->nd;
		parcoursN = parcoursN->suiv;
	}

	Nn = malloc(sizeof(CellNoeud));
	Nn->suiv = NULL;
	Nn->nd = malloc(sizeof(Noeud));
	Nn->nd->num = R->nbNoeuds;
	Nn->nd->x = x;
	Nn->nd->y = y;
	Nn->nd->voisins = NULL;
	parcoursN = Nn;
	R->nbNoeuds += 1;

	return parcoursN->nd;
}

Reseau* reconstitueReseauListe(Chaines *C) {
	if (!C) exit(0);

	Noeud *extrA, *extrB;
	CellCommodite *cc;
	CellChaine *pc;
	CellPoint *pp;
	Reseau *R = malloc(sizeof(Reseau));
	R->nbNoeuds = 0;
	R->nbNoeuds = NULL;
	R->commodites = NULL;
	cc = R->commodites;
	pc = C->chaines;

	while (pc) {
		pp = pc->points;

		while (pp->suiv) {
			extrA = rechercheCreeNoeudListe(R, pp->x, pp->y);
			extrB = rechercheCreeNoeudListe(R, pp->suiv->x, pp->suiv->y);
			majDesVoisins(extrA, extrB);
			majDesVoisins(extrB, extrA);
			pp = pp->suiv;
		}

		while (cc) cc = cc->suiv;
		cc = malloc(sizeof(CellCommodite));
		cc->extrA = rechercheCreeNoeudListe(R, pc->points->x, pc->pp->y);
		cc->extrB = extrB;
		cc->suiv = NULL;

		pc = pc->suiv;
	}

	return R;
}

void ecrireReseauTxt(Reseau *R, FILE *f) {

}

int nbLiaison(Reseau *R) {

}

int nbCommodite(Reseau *R) {

}

void afficheReseauSVG(Reseau *R, char* nomInstance) {

}

void majDesVoisins(Noeud *noeud, Noeud *voisins) {
	CellNoeud *pv;

	pv = noeud->voisins;
	while (pv) pv = pv->suiv;
	pv = malloc(sizeof(CellNoeud));
	pv->nd = voisins;                /*Ajoute plusieurs fois?*/
	pv->suiv = NULL;
}

Noeud* rechercheCreeNoeudHachage(Reseau *R, TableHachage *H, double x, double y) {
	if (!R || !H) exit(0);

	int h = fonctionHachage(clef(x, y));
	CellNoeud *parcoursN, *parcoursL;

	parcoursN = H->liste[h];
	while (parcoursN) {
		if ((parcoursN->nd->x == x) && (parcoursN->nd->y == y))
			return parcoursN->nd;
		parcoursN = parcoursN->suiv;
	}

	parcoursN = malloc(sizeof(CellNoeud));
	parcoursN->nd = malloc(sizeof(Noeud));
	parcoursN->suiv = NULL;
	parcoursN->nd->x = x;
	parcoursN->nd->y = y;
	parcourL = R->noeuds;
	H->nbE++;
	
	while (parcoursL) parcoursL = parcoursL->suiv;
	parcoursL = parcoursN;

	return parcoursN;
}

Reseau* recreeReseauHachage(Chaines *C) {
	if (!C) exit(0);

	int i;
	Noeud *extrA, *extrB;
	CellCommodite *cc;
	CellChaine *pc;
	CellPoint *pp;
	Reseau *R = malloc(sizeof(Reseau));
	TableHachage *H;

	R->nbNoeuds = 0;
	R->nbNoeuds = NULL;
	R->commodites = NULL;
	cc = R->commodites;
	pc = C->chaines;
	H = malloc(sizeof(TableHachage));
	H->m = M;
	H->nbE = 0;
	H->liste=malloc(sizeof(*CellNoeud)*M)
	for (i = 0; i < M; i++) 
		H->liste[i] = NULL;

	while (pc) {
		pp = pc->points;

		while (pp->suiv) {
			extrA = rechercheCreeNoeudHachage(R, H, pp->x, pp->y);
			extrB = rechercheCreeNoeudHachage(R, H, pp->suiv->x, pp->suiv->y);
			majDesVoisins(extrA, extrB);
			majDesVoisins(extrB, extrA);
			pp = pp->suiv;
		}

		while (cc) cc = cc->suiv;
		cc = malloc(sizeof(CellCommodite));
		cc->extrA = rechercheCreeNoeudHachage(R, H, pc->points->x, pc->pp->y);
		cc->extrB = extrB;
		cc->suiv = NULL;

		pc = pc->suiv;
	}

	return R;
}
