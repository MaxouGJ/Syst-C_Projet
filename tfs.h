#include <endian.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>



//-------------------------------------------------------
//Fonction permetant de savoir si le nom est déjà utilisé
 
int exists(char *diskname){
	struct stat s;
	return stat(diskname, &s);				// Renvoie 0 si le fichier existe -1 sinon 
}

//---------------------------------------------
//Fonction permetant de recupérer un nom valide
char * giveName(char *name){	
	while(exists(name) == 0){
		fprintf(stderr, "Erreur le nom existe déjà \nSaisissez un nom valide\n");
		scanf("%s", name);		
		name = strcat(name, ".tfs");
	}
	return name;
}


/* _____________________________________________________ */
// Fonctions exécutant des commandes.
// ---
// Commandes internes.  (builtin.c)

/*error read_physical_block(disk_id id, block b, uint32_t num); 	// Lit depuis le disque (id) le bloc b
error write_physical_block(disk_id id, block b, uint32_t num); 	// Ecrit sur le disque le bloc b
*/

// Commandes externes.  (external.c)
/*error start_disk(char *name, disk_id *id);						// Permet de manipuler un disuqe avec une identité dynamique
error read_block(disk_id id, block b, uint32_t num); 	// Permet de lire le bloc sur le disque (different de read_physical_block)
error write_block(disk_id id, block b, uint32_t num);	// Permet d'écrire sur le bloc (different de write_physical_block)
error sync_disk(disk_id id);													// Voir annexe
error stop_disk(disk_id id);													// Terminer une session de travail
*/

