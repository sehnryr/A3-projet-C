/**
 * @file visualisationC.c
 * @brief Fonction de visualisation de la consigne de chauffage
 * @authors
 * - Alexandre Auguste <alexandre.auguste@isen-ouest.yncrea.fr>
 * @date 2023-03-20
 */

#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "visualisationC.h"

void visualisationC(float puissance_f)
{
    // Tentative de lecture de data.txt

    // Si le fichier .verrouData existe, le fichier data.txt est en cours
    // d'utilisation par un autre programme, retour de la fonction.
    if (access(".verrouData", F_OK) != -1)
    {
        return;
    }
    // Sinon, création d'un fichier .verrouData qui indique que le fichier
    // data.txt est en cours de lecture par ce programme.
    else
    {
        FILE *fp2 = fopen(".verrouData", "w");
        fclose(fp2);
    }

    // Lecture du fichier data.txt
    FILE *fp = fopen("data.txt", "r");

    // Si le fichier data.txt n'existe pas, on quitte le programme.
    if (fp == NULL)
    {
        printf("Impossible d'ouvrir data.txt, arrêt du programme.\n");
        exit(1);
    }

    char tChauffe[6] = {0}; // Témoin de chauffe
    float tempInt;          // Température intérieure
    float tempExt;          // Température extérieure

    // Lecture des données du fichier data.txt
    fscanf(fp, "%s\n%f\n%f\n", tChauffe, &tempInt, &tempExt);
    fclose(fp); // Fermeture du fichier data.txt après lecture

    // Si la puissance de chauffage est positive,
    // le témoin de chauffe est à "true", sinon à "false".
    if (puissance_f > 0)
        strcpy(tChauffe, "true");
    else
        strcpy(tChauffe, "false");

    // Ouverture du fichier data.txt en écriture
    fp = fopen("data.txt", "w");

    // Ecriture des données dans le fichier data.txt
    fprintf(fp, "%s\n%f\n%f\n", tChauffe, tempInt, tempExt);
    fclose(fp); // Fermeture du fichier data.txt après écriture

    // Suppression du fichier .verrouData après manipulation du fichier data.txt
    remove(".verrouData");
}
