#include <time.h>
#include <string.h>
#include "Reseau.h"

/* auteurs:
KAMIL RZESZUTKO
CHIZHONG ZANG
*/

void afficher_menu(int* val) {
	int choix;

	printf("0- Exit\n");
	printf("1- Reconstituer le Reseau en utilisant la Liste chainee\n");
	printf("2- Reconstituer le Reseau en utilisant le Hachage\n");
	printf("3- Reconstituer le Reseau en utilisant l'Arbre\n");
	printf("4- Sauvegarder les temps de calcul les 3 structures\n");
	printf("5- e \n");
	printf("6- Enregistrement des points de deux courbes de recherche entre 1000 et 10 000 entrees\n");


	printf("Votre choix : ");
	scanf("%d", &choix);

	*val = choix;
	printf("\x1b[2J\x1b[1;1H");
}

int main(int argc, char *argv[]) {
	char *tmp = strdup(argv[0]);
	char *nomDuProgramme = strdup(tmp + 2);

	if (argc != 3) {
		printf("Erreur du format! %s <monbiblio.txt> <nblignes>\n", nomDuProgramme);
		exit(0);
	}
	int nombreDelivres = atoi(argv[2]);
	char *nomDuficherALireTXT = strdup(argv[1]);


	printf("\x1b[2J\x1b[1;1H");
	printf("Welcome !\n\n");

	do {
		afficher_menu(&choix);

		switch (choix) {
		case 0:
			printf("\x1b[2J\x1b[1;1H");
			printf("Adieu ... :'( \n");
			break;

		case 1:

			break;

		case 2:

			break;

		case 3:

			break;

		case 4:

			break;

		case 5:

			break;
		case 6:

			break;

		default:
			printf("l'option n'est pas connue!!\n");
			break;

		}

	} while (choix != 0);


	fclose(f);
	return 0;

}
