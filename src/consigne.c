#include <unistd.h>
#include "consigne.h"

float consigne(float thermostatPrec_f)
{

   float thermostat_f = 0;

   // j'essaye de lire le fichier "consigne.txt"

   // si le fichier .verrouConsigne existe, le fichier "consigne.txt" est en cours d'utilisation donc je quitte la fonction
   // la fonction access renvoie -1 si le fichier n'existe pas
   if (access(".verrouConsigne", F_OK) != -1)
   {
      printf("Impossible d'ouvrir consigne.txt, le fichier est en cours d'utilisation.\n");
      return thermostatPrec_f;
   }
   // s'il n'y en a pas qui existe, je crée un fichier .verrouConsigne qui indique que le fichier "consigne.txt" est en cours de lecture
   else
   {
      FILE *fp2;
      fp2 = fopen(".verrouConsigne", "w");
      fclose(fp2);
   }

   // je crée un pointeur de type FILE pour lire le fichier "consigne.txt"
   FILE *fp;

   // je lis le fichier "consigne.txt"
   fp = fopen("consigne.txt", "r");

   // si je n'arrive pas à ouvrir le fichier "consigne.txt", je quitte le programme
   if (fp == NULL)
   {
      printf("Impossible d'ouvrir consigne.txt, le programme va se fermer \n");
      exit(1);
   }

   // je lis le fichier "consigne.txt" et je stocke la valeur obtenu dans la variable thermostat_f
   fscanf(fp, "%f", &thermostat_f);

   // je ferme le fichier "consigne.txt"
   fclose(fp);

   // je supprime le fichier .verrouConsigne car je ne l'utilise plus
   remove(".verrouConsigne");

   // je retourne la valeur de la consigne
   return thermostat_f;
}
