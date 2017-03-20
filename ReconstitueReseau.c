#include <string.h>
#include <stdlib.h>
#include "Reseau.h"
#include "Arbre.h"

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Erreur du format! %s <NomDuInstace> <Numero de la solution>\n", argv[0]);
		exit(0);
	}

	int NumeroDeSolu = atoi(argv[2]);
	char *NomDuFicher = strdup(argv[1]);
	Reseau *r;
	FILE *f = fopen(NomDuFicher, "rb");

	FILE *f1;
	Chaines *c = lectureChaine(f);

	switch (NumeroDeSolu)
	{
	case 1:
		f1 = fopen("Reseau", "wb");
		r = reconstitueReseauListe(c);
		ecrireReseauTxt(r, f1);
		fclose(f1);
		break;

	case 2:
		f1 = fopen("Reseau", "w");
		r = recreeReseauHachage(c);
		ecrireReseauTxt(r, f1);
		fclose(f1);
		break;

	case 3:
		f1 = fopen("Reseau", "w");
		r = recreeReseauArbre(c);
		ecrireReseauTxt(r, f1);
		fclose(f1);
		break;

	default:
		printf("Le numero doit etre un entier parmis 1,2,3!!\n");
		break;
	}

	fclose(f);

	return 0;
}