#include <string.h>
#include <stdlib.h>
#include "Reseau.h"

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Erreur du format! %s <NomDuInstace> <Numero de la solution>\n", argv[0]);
		exit(0);
	}

	int NumeroDeSolu = atoi(argv[2]);
	char *NomDuFicher = strdup(argv[1]);
	Reseau *rl, *rh;
	FILE *f = fopen(strcat(NomDuFicher, ".cha"), "rb");
	FILE *f2, *f3;
	Chaines *c = lectureChaine(f);

	switch (NumeroDeSolu)
	{
	case 1:
		f2 = fopen("Reseau.txt", "w");	
		rl = reconstitueReseauListe(c);
		ecrireReseauTxt(rl, f2);
		fclose(f2);
		break;
	
	case 2:
		f3 = fopen("ReseauHachage.txt", "w");
		rh = recreeReseauHachage(c);
		ecrireReseauTxt(rh, f3);
		fclose(f3);
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