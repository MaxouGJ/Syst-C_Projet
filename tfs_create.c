#include "tfs.h"



//-------------------------------------------------
//Fonction permetant de recupérer une taille valide
int giveSize(char *taille){
	int size;
	size = atoi(taille);
	while(size <= 0){
		fprintf(stderr, "ERREUR: L'entier est trop petit ou ca n'est pas un entier\nSaisissez un nouvel entier \n");
		scanf("%d", &size);
	}
	return size;
}

//---------------------------------------------
//Fonction permetant de recupérer un nom valide
char * giveName(char *name){
    while(exists(name) == 0){
        fprintf(stderr, "ERREUR: Ce nom existe déjà \nSaisissez un nom valide\n");
        scanf("%s", name);
        name = strcat(name, ".tfs");
    }
    return name;
}

//---------------------------------
//Main permetant de créer le disque
int main(int argc,char *argv[]){
	int diskSize = 0;
	char *diskName = "disk";
	FILE *fichier;

	if (strcmp(argv[1], "-s") != 0){	//Si l'option n'est pas "-s" on affiche une erreur
		fprintf(stderr, "ERREUR DE SYNTAXE: Il faut specifier le nombre de blocs constituant le disque (option -s) \n");
	}
    
    else {
        
		if(argc >= 3)
        {
			if (argc > 3){	//L'utilisateur a choisi un nom au disque
				diskName = strcat(argv[3],".tfs");
			}
            
            else {
				diskName = "disk.tfs";
			}
            
			diskSize = giveSize(argv[2]);
			diskName = giveName(diskName);
			fichier = fopen(diskName, "w+");
			truncate(diskName, TAILLE_BLOC * diskSize);		//Permet de donner une taille x * 1024 au fichier


            //------------------------------------------------------------------------------------------------------
            //On a un fichier diskName.tfs crée avec une taille de 1024*taille soit taille bloc de 1024 octet chacun
			
			fputc(htole32(diskSize), fichier);  //taille du disque
			fputc(htole32(1), fichier);			// 1 seul partition au départ
			fputc(htole32(diskSize),fichier);
			printf("Le disque %s a été créé avec succès \n", diskName);
			
		}
        
        else {	//Il manque des argument dans l'appel a la commande
			fprintf(stderr, "ERREUR DE SYNTAXE: il n'y a pas assez d'argument");
		}
        
	}
}
