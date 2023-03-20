#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "visualisationC.h"

void visualisationC(float puissance_f)
{
   // Tentative de lecture de "data.txt"

   // si le fichier .verrouData existe, le fichier data.txt est en cours d'utilisation donc je quitte la fonction
   // la fonction fopen renvoie NULL si le fichier n'existe pas
   if (fopen("../IHM python/.verrouData", "r") == NULL)
   {
      printf("Impossible d'ouvrir data.txt, le fichier est en cours d'utilisation. Je quitte la fonction. \n");
      return;
   }
   // s'il n'y en a pas qui existe, création d'un fichier .verrouData qui indique que le fichier "data.txt" est en cours de lecture
   else
   {
      FILE *fp2;
      fp2 = fopen("../IHM python/.verrouData", "w");
      fclose(fp2);
   }

   // ceéation d'un pointeur de type FILE pour lire le fichier "data.txt"
   FILE *fp;

   // lecture du fichier "data.txt"
   fp = fopen("../IHM python/data.txt", "r");

   // si je n'arrive pas à ouvrir le fichier data.txt, je quitte le programme
   if (fp == NULL)
   {
      printf("Impossible d'ouvrir data.txt, le programme va se fermer \n");
      exit(1);
   }

   // je crée une variable de type char qui alterne entre true et false pour stocker le témoin de chauffe stockée à la premiere ligne du fichier data.txt
   char tChauffe[5];

   // je crée une variable de type float pour stocker la température extérieure stockée à la deuxieme ligne du fichier data.txt
   float tempExt;

   // je crée une variable de type float pour stocker la température interieure stockée à la troisieme ligne du fichier data.txt
   float tempInt;

   // je lis le fichier data.txt et je stocke les valeurs dans les variables créées précédemment, je les stocke car fopen ne permet pas de modifier un fichier, il faut donc tout le réecrire
   fscanf(fp, "%s %f %f", tChauffe, &tempExt, &tempInt);

   // je ferme le fichier data.txt
   fclose(fp);

   // si la puissance réçu en argument dans la fonction est supérieur à 0, le témoin de chauffe passe à true
   if (puissance_f > 0)
   {
      strcpy(tChauffe, "true");
   }
   // sinon il passe à false
   else
   {
      strcpy(tChauffe, "false");
   }

   // j'ouvre le fichier data.txt en mode écriture
   fp = fopen("../IHM python/data.txt", "w");

   // je stocke les valeurs pris en argument dans la fonction dans le fichier data.txt, ainsi que le témoin de chauffe qui ne change pas
   fprintf(fp, "%s %f %f", tChauffe, tempExt, tempInt);

   // je ferme le fichier data.txt
   fclose(fp);

   // je supprime le fichier .verrouData car je ne l'utilise plus
   remove("../IHM python/.verrouData");
}
