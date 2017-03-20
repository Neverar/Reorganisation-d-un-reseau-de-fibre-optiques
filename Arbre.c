#include <stdlib.h>
#include <stdio.h>
#include "Arbre.h"

void chaineCoordMinMax(Chaines *C, double *xmin, double *ymin, double *xmax, double *ymax)
{
    if (!C)
        exit(0);

    CellChaine *pc = C->chaines;
    CellPoint *pp;

    *xmin = C->chaines->points->x;
    *xmax = C->chaines->points->x;
    *ymin = C->chaines->points->y;
    *ymax = C->chaines->points->y;

    while (pc)
    {
        pp = pc->points;

        while (pp)
        {
            if ((pp->x) <= *xmin)
                *xmin = pp->x;
            if ((pp->x) > *xmax)
                *xmax = pp->x;
            if ((pp->y) <= *ymin)
                *ymin = pp->y;
            if ((pp->y) > *ymax)
                *ymax = pp->y;

            pp = pp->suiv;
        }
        pc = pc->suiv;
    }
}

ArbreQuat *creerArbreQuat(double xc, double yc, double coteX, double coteY)
{
    ArbreQuat *arbre = malloc(sizeof(ArbreQuat));
    if (!arbre)
    {
        printf("Erreur d'allocation d'arbre\n");
        exit(1);
    }
    arbre->xc = xc;
    arbre->yc = yc;
    arbre->coteX = coteX;
    arbre->coteY = coteY;
    arbre->noeud = NULL;
    arbre->so = NULL;
    arbre->se = NULL;
    arbre->no = NULL;
    arbre->ne = NULL;
    return arbre;
}

ArbreQuat *insererNoeudArbre(Noeud *n, ArbreQuat *a, ArbreQuat *parent){
    if(!a){
         
        if((n->x<parent->xc)&&(n->y<parent->yc)){
           
            a = creerArbreQuat((parent->xc)-(parent->coteX)/4, (parent->yc)-(parent->coteY)/4 , parent->coteX/2, parent->coteY/2);
          
        }

        if((n->x>=parent->xc)&&(n->y<parent->yc)){
            a = creerArbreQuat((parent->xc)+(parent->coteX)/4, (parent->yc)-(parent->coteY)/4, parent->coteX/2, parent->coteY/2);
            
        }

        if((n->x<parent->xc)&&(n->y>=parent->yc)){
            a = creerArbreQuat((parent->xc)-(parent->coteX)/4, (parent->yc)+(parent->coteY)/4, parent->coteX/2, parent->coteY/2);
            
        }

        if((n->x>=parent->xc)&&(n->y>=parent->yc)){
            a = creerArbreQuat((parent->xc)+(parent->coteX)/4, (parent->yc)+(parent->coteY)/4, parent->coteX/2, parent->coteY/2);
            
        }

        a->noeud=n;

    }

    else if((a!=NULL)&&(a->noeud!=NULL)){
         
        if((n->x<a->xc)&&(n->y<a->yc)){
             
            a->so=insererNoeudArbre(n, a->so, a);
          
        }

        else if((n->x>=a->xc)&&(n->y<a->yc)){
           
            a->se = insererNoeudArbre(n, a->se, a);
        }

        else if((n->x<a->xc)&&(n->y>=a->yc)){
             
            a->no = insererNoeudArbre(n, a->no, a);
            
        }

        else if((n->x>=a->xc)&&(n->y>=a->yc)){
            a->ne = insererNoeudArbre(n, a->ne, a);
            
        }

        if((a->noeud->x<a->xc)&&(a->noeud->y<a->yc)){
             
            a->so=insererNoeudArbre(a->noeud, a->so, a);
          
        }

       if((a->noeud->x>=a->xc)&&(a->noeud->y<a->yc)){
             
            a->se=insererNoeudArbre(a->noeud, a->se, a);
          
        }

        if((a->noeud->x<a->xc)&&(a->noeud->y>=a->yc)){
             
            a->no=insererNoeudArbre(a->noeud, a->no, a);

        
          
        }

       
       if((a->noeud->x>=a->xc)&&(a->noeud->y>=a->yc)){
            a->ne = insererNoeudArbre(a->noeud, a->ne, a);
            
        }
       
       a->noeud = NULL; 
    }

    else if((a!=NULL)&&(!(a->noeud))){
        if((n->x<a->xc)&&(n->y<a->yc)){
            a->so=insererNoeudArbre(n, a->so, a);
          
        }

        if((n->x>=a->xc)&&(n->y<a->yc)){
            a->se = insererNoeudArbre(n, a->se, a);
        }

        if((n->x<a->xc)&&(n->y>=a->yc)){
            a->no = insererNoeudArbre(n, a->no, a);
            
        }

        if((n->x>=a->xc)&&(n->y>=a->yc)){
            a->ne = insererNoeudArbre(n, a->ne, a);
            
        }
    }

    return a;

}

Noeud *chercherNoeudArbre(CellPoint *pt, Reseau *R, ArbreQuat **aptr, ArbreQuat *parent){
    Noeud *n;
    
    if(*aptr == NULL){
         if((pt->x == 55)&&(pt->y == 201))
            printf("55 -1\n");
        n = malloc(sizeof(Noeud));
        n->voisins = NULL;
        n->x = pt->x;
        n->y = pt->y;
        R->nbNoeuds+=1;
        n->num = R->nbNoeuds;
        *aptr = insererNoeudArbre(n, *aptr, parent);
        R->noeuds = AjouterTeteNoeud(R->noeuds, n);
        return n;
    }

    else if((*aptr)&&((*aptr)->noeud)){
        
        if((((*aptr)->noeud->x)==(pt->x))&&(((*aptr)->noeud->y)==(pt->y))){
            
            return (*aptr)->noeud;
        }

  
        n = malloc(sizeof(Noeud));
        n->voisins = NULL;
        n->x = pt->x;
        n->y = pt->y;
        R->nbNoeuds+=1;
        n->num = R->nbNoeuds;
       
        *aptr = insererNoeudArbre(n, *aptr, parent);
        (*aptr)->noeud = NULL;
        R->noeuds = AjouterTeteNoeud(R->noeuds, n);
        return n;
    } 

     else if((*aptr)&&((*aptr)->noeud == NULL)){
         
        if((pt->x<(*aptr)->xc)&&(pt->y<(*aptr)->yc)){
            if((pt->x == 55)&&(pt->y == 201))
            printf("55 -31\n");
            return chercherNoeudArbre(pt, R, &((*aptr)->so), *aptr);
          
        }

        if((pt->x>=(*aptr)->xc)&&(pt->y<(*aptr)->yc)){
            if((pt->x == 55)&&(pt->y == 201))
            printf("55 -32\n");
            return chercherNoeudArbre(pt, R, &((*aptr)->se), *aptr);
          
        }
        if((pt->x<(*aptr)->xc)&&(pt->y>=(*aptr)->yc)){
            if((pt->x == 55)&&(pt->y == 201))
            printf("55 -33\n");
            return chercherNoeudArbre(pt, R, &((*aptr)->no), *aptr);
          
        }
        if((pt->x>=(*aptr)->xc)&&(pt->y>=(*aptr)->yc)){
            if((pt->x == 55)&&(pt->y == 201))
            printf("55 -34\n");
            return chercherNoeudArbre(pt, R, &((*aptr)->ne), *aptr);
          
        }
     }
}

Reseau *recreeReseauArbre(Chaines *C){
    if (!C)
		exit(0);
    
    double xmin, xmax, ymin, ymax; 
	Noeud *extrA, *extrB;
	CellChaine *pc;
	CellPoint *pp;
    ArbreQuat *parent, *a = NULL;
	Reseau *R = malloc(sizeof(Reseau));
	
    R->nbNoeuds = 0;
	R->noeuds = NULL;
	R->commodites = NULL;
	R->gamma = C->gamma;
	pc = C->chaines;

    chaineCoordMinMax(C, &xmin, &ymin, &xmax, &ymax);
    parent = creerArbreQuat(xmax, ymin, 2*(xmax-xmin), 2*(ymax-ymin));

	while (pc)
	{
		pp = pc->points;

		while (pp->suiv)
		{
			extrA = chercherNoeudArbre(pp, R, &a, parent);
			extrB = chercherNoeudArbre(pp->suiv, R, &a, parent);             
			majDesVoisins(extrA, extrB);
			majDesVoisins(extrB, extrA);
			pp = pp->suiv;
		}
		extrA = chercherNoeudArbre(pc->points, R, &a, parent);;
		R->commodites = AjouterTeteCommodite(R->commodites, extrA, extrB);
		pc = pc->suiv;
	}

	return R;
}
