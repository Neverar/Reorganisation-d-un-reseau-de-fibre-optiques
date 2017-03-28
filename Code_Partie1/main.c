#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include "Reseau.h"
#include "Arbre.h"

/* auteurs:
KAMIL RZESZUTKO
CHIZHONG ZANG
*/

void afficher_menu(int *val)
{
	int choix;

	printf("0- Exit\n");
	printf("1- Reconstituer les Reseaux en lisant les chaines\n");
	printf("2- Calculer et sauvgarder les tmeps de la reconstruction les 3 structures\n");

	printf("Votre choix : ");
	scanf("%d", &choix);

	*val = choix;
	printf("\x1b[2J\x1b[1;1H");
}

int main(int argc, char *argv[])
{
	FILE *f, *reseaux, *tmpsCalc;
	float duration;
	clock_t start, finish;
	DIR *dir;
	struct dirent *ptr;
	Reseau *r = NULL;
	Chaines *c = NULL;
	int choix, nbPoints;
	char repoE[255], repoR[255], fr[255];

	printf("\x1b[2J\x1b[1;1H");
	printf("Welcome !\n\n");

	do
	{
		afficher_menu(&choix);

		switch (choix)
		{
		case 0:
			printf("\x1b[2J\x1b[1;1H");
			printf("Adieu ... :'( \n");
			break;

		case 1:
			dir = opendir("Instances_cha");
			if (!dir)
			{
				printf("repo n'existe pas\n");
				exit(0);
			}

			while ((ptr = readdir(dir)) != NULL) {
				if ((strcmp(ptr->d_name, "..") != 0) && (strcmp(ptr->d_name, ".") != 0) && (strcmp(ptr->d_name, "desktop.ini") != 0))
				{
					strcpy(repoE, "Instances_cha/");
					strcpy(repoR, "Instances_res/");
					f = fopen(strcat(repoE, ptr->d_name), "rb");
					c = lectureChaine(f);
					strcpy(fr, ptr->d_name);

					fr[strlen(fr) - 3] = 'r';
					fr[strlen(fr) - 2] = 'e';
					fr[strlen(fr) - 1] = 's';

					reseaux = fopen(strcat(repoR, fr), "wb");
					r = recreeReseauArbre(c);
					ecrireReseauTxt(r, reseaux);


					fclose(f);
					fclose(reseaux);
				}
			}

			closedir(dir);

			break;

		case 2:

			dir = opendir("Instances_cha");
			if (!dir)
			{
				printf("repo n'existe pas\n");
				exit(0);
			}

			while ((ptr = readdir(dir)) != NULL) {
				if ((strcmp(ptr->d_name, "..") != 0) && (strcmp(ptr->d_name, ".") != 0) && (strcmp(ptr->d_name, "desktop.ini") != 0))
				{
					strcpy(repoE, "Instances_cha/");
					strcpy(repoR, "Tmps/");
					f = fopen(strcat(repoE, ptr->d_name), "rb");
					c = lectureChaine(f);
					nbPoints = comptePointsTotal(c);
					strcpy(fr, ptr->d_name);

					/* Liste Chainee */
					start = clock();
					r = reconstitueReseauListe(c);
					finish = clock();
					duration = (finish - start);

					tmpsCalc = fopen(strcat(repoR, "Liste"), "a+");
					fprintf(tmpsCalc, "%s:   %.2f %d\n", ptr->d_name, duration, nbPoints);

					fclose(tmpsCalc);

					/* Hachage */
					strcpy(repoR, "Tmps/");
					start = clock();
					r = recreeReseauHachage(c);
					finish = clock();
					duration = (finish - start);

					tmpsCalc = fopen(strcat(repoR, "Hachage"), "a+");
					fprintf(tmpsCalc, "%s:   %.2f %d\n", ptr->d_name, duration, nbPoints);

					fclose(tmpsCalc);

					/* Arbre */
					strcpy(repoR, "Tmps/");
					start = clock();
					r = recreeReseauArbre(c);
					finish = clock();
					duration = (finish - start);

					tmpsCalc = fopen(strcat(repoR, "Arbre"), "a+");
					fprintf(tmpsCalc, "%s:   %.2f %d\n", ptr->d_name, duration, nbPoints);

					fclose(tmpsCalc);

					fclose(f);
				}
			}
			break;

		default:
			printf("l'option n'est pas connue!!\n");
			break;
		}

	} while (choix != 0);

	fclose(f);
	return 0;
}
