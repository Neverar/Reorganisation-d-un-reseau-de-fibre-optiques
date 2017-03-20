#include "Chaine.h"
#include "entree_sortie.h"
#include "SVGwriter.h"
#include <math.h>
#include <stdlib.h>
#define TMAX 1000

Chaines *lectureChaine(FILE *f)
{
	if (!f)
		exit(0);

	char buffe[255];
	int i = 0, j, numero, nbPoints;
	double x, y;
	CellPoint *Cp = NULL;

	Chaines *c = malloc(sizeof(Chaines));
	if (!c)
	{
		printf("echec d'alloer mermoires\n ");
		exit(0);
	}
	GetChaine(f, TMAX, buffe);
	c->nbChaines = GetEntier(f);
	GetChaine(f, TMAX, buffe);
	c->gamma = GetEntier(f);
	c->chaines = NULL;

	while (i != c->nbChaines)
	{

		numero = GetEntier(f);
		nbPoints = GetEntier(f);

		for (j = 0; j < nbPoints; j++)
		{
			x = GetReel(f);
			y = GetReel(f);
			Cp = AjouterTetePoint(Cp, x, y);
		}

		c->chaines = AjouterTeteChaine(c->chaines, Cp, numero, nbPoints);
		Cp = NULL;
		i++;
	}

	return c;
}

void ecrireChaineTxt(Chaines *C, FILE *f)
{
	if ((!f) || (!C))
		exit(0);

	int i, k;
	CellChaine *pc, *c = NULL;
	CellPoint *pp, *p = NULL;

	fprintf(f, "NbChain: %d\n", C->nbChaines);
	fprintf(f, "Gamma: %d\n\n", C->gamma);

	pc = C->chaines;
	while (pc)
	{
		pp = pc->points;

		while (pp)
		{
			p = AjouterTetePoint(p, pp->x, pp->y);
			pp = pp->suiv;
		}
		c = AjouterTeteChaine(c, p, pc->numero, pc->nbPoints);
		p = NULL;
		pc = pc->suiv;
	}

	for (i = 0; i < C->nbChaines; i++)
	{
		fprintf(f, "%d", c->numero);
		fprintf(f, " %d", c->nbPoints);

		for (k = 0; k < c->nbPoints; k++)
		{
			fprintf(f, " %.2f %.2f", c->points->x, c->points->y);
			c->points = c->points->suiv;
		}

		c = c->suiv;
		fprintf(f, "\n");
	}
}

void afficheChaineSVG(Chaines *C, char *nomInstance)
{
	if (!C)
		exit(0);

	CellChaine *parcoursC;
	CellPoint *parcoursP;
	SVGwriter *svg = malloc(sizeof(SVGwriter));

	SVGinit(svg, nomInstance, 100, 100);
	SVGpointColor(svg, Black);
	parcoursC = C->chaines;

	while (parcoursC)
	{
		SVGlineRandColor(svg);
		parcoursP = parcoursC->points;

		while (parcoursP->suiv->suiv)
		{
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
double longueurTotale(Chaines *C)
{
	int i, k;
	double sommeUneChaine = 0;
	double sommeTotal = 0;
	for (i = 0; i < C->nbChaines; i++)
	{
		for (k = 0; k < (C->chaines->nbPoints - 1); k++)
		{

			sommeUneChaine = sommeUneChaine + sqrt((C->chaines->points->suiv->x - C->chaines->points->x) * (C->chaines->points->suiv->x - C->chaines->points->x) +
				(C->chaines->points->suiv->y - C->chaines->points->y) * (C->chaines->points->suiv->y - C->chaines->points->y));

			C->chaines->points = C->chaines->points->suiv; /* Pareil, faut creer un parcours */
		}
		sommeTotal = sommeTotal + sommeUneChaine;
		C->chaines = C->chaines->suiv; /* faut creer un parcours */
	}

	return sommeTotal;
}

int comptePointsTotal(Chaines *C)
{
	if (!C)
		exit(0);

	int cpt = 0;
	CellChaine *parcoursC;

	parcoursC = C->chaines;

	while (parcoursC)
	{
		cpt += parcoursC->nbPoints;
		parcoursC = parcoursC->suiv;
	}
	return cpt;
}

CellPoint *AjouterTetePoint(CellPoint *p, double x, double y)
{
	CellPoint *np = malloc(sizeof(CellPoint));

	np->x = x;
	np->y = y;
	np->suiv = p;

	return np;
}

CellChaine *AjouterTeteChaine(CellChaine *c, CellPoint *Nouvp, int num, int nbP)
{
	CellChaine *nc = malloc(sizeof(CellChaine));

	nc->points = Nouvp;
	nc->numero = num;
	nc->nbPoints = nbP;
	nc->suiv = c;

	return nc;
}