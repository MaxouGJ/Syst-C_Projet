#include "tfs.h"


int main(int argc,char *argv[]){
	char *diskName = "disk.tfs";
	FILE *fichier;
	int i;
	int x = 1;
	int taille, partition;
	
	if(argc > 1)
		diskName = strcat(argv[1], ".tfs");
	if(exists(diskName) != 0){
		fprintf(stderr, "Erreur le disque %s n'existe pas", diskName);
	}else{
		fichier = fopen(diskName, "r");	//On ouvre le fichier
		if(fichier != NULL)
		{
			for(i = 0; i<256; i++)
			{				
				if(i == 0)
				{
					taille = fgetc(fichier);
					printf("Il y a %d bloc dans le disque et sa taille est de %d. \n", taille, (taille*1024));
				}else if(i == 1){
					partition = fgetc(fichier);
					printf("Il y a %d partition.\n", partition);
				}else
				{
					partition = fgetc(fichier);
					if(partition != 0 && partition != -1){						
						printf("La partiton %d a une taille %d \n",x, partition);
						x++;
					}
				}
			}	
		}
		else
			fprintf(stderr,"Erreur a l'ouverture du fichier verifiez vos droits");
	}
}
