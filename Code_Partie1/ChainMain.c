#include <string.h>
#include <stdlib.h>
#include "Chaine.h"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Erreur du format! %s <NomDuFicher>\n", argv[0]);
		exit(0);
	}

	char *NomDuFicher = strdup(argv[1]);
	FILE *f = fopen(NomDuFicher, "rb");
	FILE *f2 = fopen("Chaine", "w"); 
	Chaines *c = lectureChaine(f);
	ecrireChaineTxt(c, f2);

	fclose(f);
	fclose(f2);

	return 0;
}