#include <endian.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define TAILLE_BLOC 1024

//-------------------------------------------------------
// Definition des structures Disk et Bloc
// ---
//typedef uint32_t 	uint_least32_t;

typedef struct Disk Disk;
struct Disk {
    int disk_id;    //identité du disque
    char* name;     //nom du disque
    int size;       //nbr de blocks constituant le disque
};

typedef struct Block Block;
struct Block {
   	//uint32_t num;       //numero du bloc
    const int taille;   //taille du bloc
};


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

//-------------------------------------------------------
//Fonction permetant de savoir si le nom est déjà utilisé
//Renvoie 0 si le fichier existe -1 sinon
int exists(char *diskname){
    struct stat s;
    return stat(diskname, &s);
}

