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
	int taille = 0;
	char *diskName = "disk";
	FILE *fichier;

	if (strcmp(argv[1], "-s") != 0)
	{					//Si l'option n'est pas "-s" on affiche une erreur
		fprintf(stderr, "Erreur l'option %s n'existe pas \n",argv[1]);
	}else
	{
		if(argc >= 3)
		{			
			if (argc >3)			//Il y a le nom du disque
			{			
				diskName = strcat(argv[3],".tfs");
			}else
			{	
				diskName = "disk.tfs";
			}
			/*
			if (argc >3)			//Il y a le nom du disque
			{			
				diskName = argv[3];
			}else
			{	
				diskName = "disk"; //pointeur dans une region de mémoire ou l'on peut pas ecrire utiliser strcopy
			}
			diskName = strcat(diskName, ".tfs");
			*/
			
			taille = diskSize(argv[2]);
			diskName = giveName(diskName);
			fichier = fopen(diskName, "w+");
			truncate(diskName, 1024*taille);		//Permet de donner une taille x * 1024 au fichier		


//----------------------------------------------------------------------------------------------------
//On a un fichier diskName.tfs crée avec une taille de 1024*taille soit taille bloc de 1024 octet chacun
			
			fputc(htole32(taille), fichier); //taille du disque
			fputc(htole32(1), fichier);			// 1 seul partition au départ
			fputc(htole32(taille),fichier);
			printf("Le disque %s a été créé avec succès \n", diskName);
			
		}else			//Il manque des argument dans l'appel a la commande
		{	
			fprintf(stderr, "Erreur il n'y a pas assez d'argument");		
		}
	}
}
