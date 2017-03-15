#include <string.h>
#include <stdlib.h>
#include "Reseau.h"

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Erreur du format! %s <NomDuInstace.cha> <Numero de la solution>\n", argv[0]);
		exit(0);
	}

	int NumeroDeSolu = atoi(argv[2]);
	char *NomDuFicher = strdup(argv[1]);
	Reseau *r;
	FILE *f = fopen(NomDuFicher, "rb");
	Chaines *c = lectureChaine(f);

	switch (NumeroDeSolu)
	{
	case 1:
		r = reconstitueReseauListe(c);
		break;
	case 2:
		r = recreeReseauHachage(c);
		break;
	/*case 3:
		break;*/
	default:
		printf("Le numero doit etre un entier parmis 1,2,3!!\n");
		break;
	}

	fclose(f);
	return 0;
}