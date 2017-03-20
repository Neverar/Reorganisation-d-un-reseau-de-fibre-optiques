#include <stdlib.h>
#include <stdio.h>
#include "Reseau.h"
#include "Hachage.h"

#define M 100000

Noeud *rechercheCreeNoeudListe(Reseau *R, double x, double y)
{
	if (!R)
		exit(0);

	CellNoeud *parcoursN;
	Noeud *Nn;
	parcoursN = R->noeuds;

	while (parcoursN)
	{
		if ((parcoursN->nd->x == x) && (parcoursN->nd->y == y))
			return parcoursN->nd;
		parcoursN = parcoursN->suiv;
	}

	Nn = malloc(sizeof(Noeud));
	Nn->x = x;
	Nn->y = y;
	Nn->voisins = NULL;
	R->nbNoeuds += 1;
	Nn->num = R->nbNoeuds;
	R->noeuds = AjouterTeteNoeud(R->noeuds, Nn);

	return Nn;
}

Reseau *reconstitueReseauListe(Chaines *C)
{
	if (!C)
		exit(0);

	Noeud *extrA, *extrB;
	CellChaine *pc;
	CellPoint *pp;
	Reseau *R = malloc(sizeof(Reseau));
	R->nbNoeuds = 0;
	R->noeuds = NULL;
	R->commodites = NULL;
	R->gamma = C->gamma;
	pc = C->chaines;

	while (pc)
	{
		pp = pc->points;

		while (pp->suiv)
		{
			extrA = rechercheCreeNoeudListe(R, pp->x, pp->y);
			extrB = rechercheCreeNoeudListe(R, pp->suiv->x, pp->suiv->y);
			majDesVoisins(extrA, extrB);
			majDesVoisins(extrB, extrA);
			pp = pp->suiv;
		}
		extrA = rechercheCreeNoeudListe(R, pc->points->x, pc->points->y);
		R->commodites = AjouterTeteCommodite(R->commodites, extrA, extrB);

		pc = pc->suiv;
	}

	return R;
}

void ecrireReseauTxt(Reseau *R, FILE *f)
{
	if ((!R) || (!f))
		exit(0);

	CellNoeud *parcoursN = R->noeuds, *parcoursV;
	CellCommodite *parcoursC = R->commodites;

	fprintf(f, "NbNoeuds: %d\n", R->nbNoeuds);
	fprintf(f, "NbLiaison: %d\n", nbLiaison(R));
	fprintf(f, "NbCommodite: %d\n", nbCommodite(R));
	fprintf(f, "Gamma: %d\n\n", R->gamma);

	while (parcoursN)
	{
		fprintf(f, "V %d %.6f %.6f\n", parcoursN->nd->num, parcoursN->nd->x, parcoursN->nd->y);
		parcoursN = parcoursN->suiv;
	}

	fprintf(f, "\n");
	parcoursN = R->noeuds;
	while (parcoursN)
	{
		parcoursV = parcoursN->nd->voisins;

		while (parcoursV)
		{
			if (parcoursV->nd->num < parcoursN->nd->num)
				fprintf(f, "l %d %d\n", parcoursV->nd->num, parcoursN->nd->num);

			parcoursV = parcoursV->suiv;
		}
		parcoursN = parcoursN->suiv;
	}

	fprintf(f, "\n");
	while (parcoursC)
	{
		fprintf(f, "k %d %d\n", parcoursC->extrA->num, parcoursC->extrB->num);
		parcoursC = parcoursC->suiv;
	}
}

int nbLiaison(Reseau *R)
{
	if (!R)
		exit(0);

	int cpt = 0;
	CellNoeud *parcoursN = R->noeuds, *parcoursV;

	while (parcoursN)
	{
		parcoursV = parcoursN->nd->voisins;

		while (parcoursV)
		{
			cpt++;
			parcoursV = parcoursV->suiv;
		}

		parcoursN = parcoursN->suiv;
	}

	return (cpt / 2);
}

int nbCommodite(Reseau *R)
{
	if (!R)
		exit(0);

	int cpt = 0;
	CellCommodite *parcoursC = R->commodites;

	while (parcoursC)
	{
		cpt++;
		parcoursC = parcoursC->suiv;
	}
	return cpt;
}

void afficheReseauSVG(Reseau *R, char *nomInstance)
{
}

void majDesVoisins(Noeud *noeud, Noeud *voisins)
{
	CellNoeud *pn = noeud->voisins;

	while (pn)
	{
		if (pn->nd->num == voisins->num)
			return;
		pn = pn->suiv;
	}

	noeud->voisins = AjouterTeteNoeud(noeud->voisins, voisins);
}

Noeud *rechercheCreeNoeudHachage(Reseau *R, TableHachage *H, double x, double y)
{
	if (!R || !H)
		exit(0);

	int h = fonctionHachage(clef(x, y), H->m);
	CellNoeud *parcoursN;
	Noeud *Nn;

	printf("h=%d\n", h);
	parcoursN = H->liste[h];
	
	while (parcoursN)
	{
		if ((parcoursN->nd->x == x) && (parcoursN->nd->y == y))
			return parcoursN->nd;
		parcoursN = parcoursN->suiv;
	}

	Nn = malloc(sizeof(Noeud));
	Nn->x = x;
	Nn->y = y;
	Nn->voisins = NULL;
	R->nbNoeuds += 1;
	Nn->num = R->nbNoeuds;
	R->noeuds = AjouterTeteNoeud(R->noeuds, Nn);

	H->nbE++;
	H->liste[h] = AjouterTeteNoeud(H->liste[h], Nn);

	return Nn;
}

Reseau *recreeReseauHachage(Chaines *C)
{
	if (!C)
		exit(0);

	int i;
	Noeud *extrA, *extrB;
	CellChaine *pc;
	CellPoint *pp;
	Reseau *R = malloc(sizeof(Reseau));
	TableHachage *H;

	R->nbNoeuds = 0;
	R->gamma = C->gamma;
	R->noeuds = NULL;
	R->commodites = NULL;
	pc = C->chaines;
	H = malloc(sizeof(TableHachage));
	H->m = M;
	H->nbE = 0;
	H->liste = malloc(sizeof(CellNoeud *) * M);
	for (i = 0; i < M; i++)
		H->liste[i] = NULL;

	while (pc)
	{
		pp = pc->points;

		while (pp->suiv)
		{
			extrA = rechercheCreeNoeudHachage(R, H, pp->x, pp->y);
			extrB = rechercheCreeNoeudHachage(R, H, pp->suiv->x, pp->suiv->y);
			majDesVoisins(extrA, extrB);
			majDesVoisins(extrB, extrA);
			pp = pp->suiv;
		}

		extrA = rechercheCreeNoeudHachage(R, H, pc->points->x, pc->points->y);
		R->commodites = AjouterTeteCommodite(R->commodites, extrA, extrB);

		pc = pc->suiv;
	}

	return R;
}

CellNoeud *AjouterTeteNoeud(CellNoeud *n, Noeud *Nouv)
{
	CellNoeud *Nn = malloc(sizeof(CellNoeud));
	Nn->nd = Nouv;
	Nn->suiv = n;

	return Nn;
}

CellCommodite *AjouterTeteCommodite(CellCommodite *c, Noeud *A, Noeud *B)
{
	CellCommodite *Nc = malloc(sizeof(CellCommodite));
	Nc->extrA = A;
	Nc->extrB = B;
	Nc->suiv = c;

	return Nc;
}