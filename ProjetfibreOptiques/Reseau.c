#include<stdlib.h>
#include<stdio.h>
#include "Reseau.h"

Noeud* rechercherCreeNoeudListe(Reseau *R, double x, double y) {
	if (!R) exit(0);

	CellNoeud *parcoursN, *Nn;
	int cpt = 0;

	parcoursN = R->noeuds;
	while (parcoursN) {
		if ((parcoursN->nd->x == x) && (parcoursN->nd->y == y))
			return parcoursN->nd;
		parcoursN = parcoursN->suiv;
		cpt++;
	}
	Nn = malloc(sizeof(CellNoeud));
	Nn->suiv = NULL;
	Nn->nd = malloc(sizeof(Noeud));
	Nn->nd->num = cpt + 1;
	Nn->nd->x = x;
	Nn->nd->y = y;
	Nn->nd->voisins = NULL;
	parcoursN = Nn;

	return parcoursN->nd;
}

Reseau* reconstitueReseauListe(Chaines *C) {
	if (!C) exit(0);


}

void ecrireReseauTxt(Reseau *R, FILE *f) {

}

int nbLiaison(Reseau *R) {

}

int nbCommodite(Reseau *R) {

}

void afficheReseauSVG(Reseau *R, char* nomInstance) {

}