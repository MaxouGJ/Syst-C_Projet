#include "tfs.h"

//-------------------------------------------------
//Fonction permetant de recupérer une taille valide
int diskSize(char *taille){
	int size;
	size = atoi(taille);
	while(size <= 0){
		fprintf(stderr, "Erreur l'entier l'entier est trop petit ou ca n'est pas un entier\nSaisissez un nouvel entier \n");
		scanf("%d", &size);
	}
	return size;
}


//---------------------------------
//Main permetant de créer le disque
int main(int argc,char *argv[]){
	int taille = 0, i, tailleMax,tailleAct = 0, taillePart1, nbPart = 0;
	char *diskName = "disk.tfs";
	FILE *fichier;
	int b = 0,test;
	
	diskName = strcat(argv[argc -1],".tfs");
	if(exists(diskName) == 0)
	{
		fichier = fopen(diskName, "r+");
		tailleMax = fgetc(fichier) * 1024;		
		nbPart = fgetc(fichier);
		taillePart1 = fgetc(fichier);
		while(b == 0){
			test = fgetc(fichier);
			if(test == -1 || test ==0)
				b = 1;
			else 
				tailleAct = tailleAct + test;
		}	
		fseek(fichier, -1, SEEK_CUR);
		for(i = 0; i< argc -1; i++)
		{						
			if(i % 2 != 0){			
				if  (strcmp(argv[i], "-p") != 0)
				{					//Si l'option n'est pas "-s" on affiche une erreur
					fprintf(stderr, "Erreur l'option %s n'existe pas. \nLa commande est de la forme tfs_partition -p size [-p size] ... [name].\n",argv[i]);
				}else{
					taille = atoi(argv[i+1]);
					if(tailleAct + taille > tailleMax)
						fprintf(stderr, "Erreur votre disque n'est pas assez grand");
					else{
						tailleAct = tailleAct + taille;
						nbPart++;
						int x = fputc(htole32(taille), fichier); //taille du disque
					}
				}
			}
		}
		rewind(fichier);
		fseek(fichier, 1,SEEK_SET);
		fputc(htole32(nbPart), fichier); //taille du disque		
		if(taillePart1 == 0 || taillePart1 == -1){
			fputc(htole32(tailleMax- tailleAct),fichier);
		}
	}	
	else
	{
		fprintf(stderr, "Erreur le fichier %s n'existe pas", diskName);
	}
}
