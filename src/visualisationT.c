#include <unistd.h>
#include "visualisationT.h"

void visualisationT(temp_t myTemp)
{
    // j'essaye de lire le fichier data.txt
    
    // si le fichier .verrouData existe, le fichier data.txt est en cours d'utilisation donc je quitte la fonction
    // la fonction access renvoie -1 si le fichier n'existe pas
    if(access(".verrouData", F_OK) != -1) 
    {
        printf("Impossible d'ouvrir data.txt, le fichier est en cours d'utilisation.\n");
        return;
    }
    // s'il n'y en a pas qui existe, je crée un fichier .verrouData qui indique que le fichier data.txt est en cours de lecture
    else 
    {
        FILE *fp2;
        fp2 = fopen(".verrouData", "w");
        fclose(fp2);
    }
        
    // je crée un pointeur de type FILE pour lire le fichier data.txt
    FILE *fp;

    // je lis le fichier data.txt
    fp = fopen("data.txt", "r");

    // si je n'arrive pas à ouvrir le fichier data.txt, je quitte le programme
    if (fp == NULL)
    {
        printf("Impossible d'ouvrir data.txt, le programme va se fermer. \n");
        exit(1);
    }
    
    // je crée une variable de type char qui alterne entre true et false pour stocker le témoin de chauffe stockée à la premiere ligne du fichier data.txt
    char tChauffe[8];

    // je crée une variable de type float pour stocker la température extérieure stockée à la deuxieme ligne du fichier data.txt, ici elle ne me sert à rien mais je la laisse pour que le code soit plus clair car je l'utilise dans visualisationC.c. Cela peut aussi me permettre de l'afficher si j'en ai besoin (pour débuguer ou voir son évolution). 
    float tempExt; 

    // je crée une variable de type float pour stocker la température interieure stockée à la troisieme ligne du fichier data.txt, ici elle ne me sert à rien mais je la laisse pour que le code soit plus clair car je l'utilise dans visualisationT.c. Cela peut aussi me permettre de l'afficher si j'en ai besoin (pour débuguer ou voir son évolution). 
    float tempInt;

    // je lis le fichier data.txt et je stocke les valeurs dans les variables créées précédemment, je les stocke car fopen ne permet pas de modifier un fichier, il faut donc tout le réecrire
    fscanf(fp, "%s %f %f", tChauffe, &tempExt, &tempInt);

    // fermeture du fichier data.txt
    fclose(fp);

    // j'ouvre le fichier data.txt en mode écriture
    fp = fopen("data.txt", "w");

    // je stocke les valeurs pris en argument dans la fonction dans le fichier data.txt, ainsi que le témoin de chauffe qui ne change pas
    fprintf(fp, "%s\n%f\n%f\n", tChauffe, myTemp.interieure, myTemp.exterieure);

    // je ferme le fichier "data.txt"
    fclose(fp);

    // je supprime le fichier .verrouData car je ne l'utilise plus
    remove(".verrouData");
}
