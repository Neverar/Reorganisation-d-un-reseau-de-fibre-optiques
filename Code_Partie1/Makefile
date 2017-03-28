GCC_FLAGS = -Wall -g -lm

all: main

main : main.c SVGwriter.c Reseau.c Chaine.c Hachage.c Arbre.c entree_sortie.c 
		gcc ${GCC_FLAGS} main.c SVGwriter.c Reseau.c Chaine.c Hachage.c Arbre.c entree_sortie.c 
clean : 
	rm -f *.o *~ biblio Tmps/* Reseau Chaine a.out ReconstitueReseau
