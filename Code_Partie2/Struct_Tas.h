#ifndef _STRUCT_TAS_H
#define _STRUCT_TAS_H

#define CAPACITE_MAX 100000

typedef struct{
    int i;
    double c;
} Element;

typedef struct{
    int n;
    Element *tab[CAPACITE_MAX + 1];
} Tas;

Element *min(Tas *t);
Element *insert(Tas *t, Element *e);
void suppMin(Tas *t);
int exist(Tas *t, int i);
    
#endif
