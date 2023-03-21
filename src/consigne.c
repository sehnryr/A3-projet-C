/**
 * @file consigne.c
 * @brief Fonction de récupération de la consigne de température
 * @authors
 * - Alexandre Auguste <alexandre.auguste@isen-ouest.yncrea.fr>
 * @date 2023-03-20
 */

#include <unistd.h>
#include "consigne.h"

/**
 * @brief Récupère la consigne de température
 *
 * @param thermostatPrec_f Ancienne consigne
 * @return Consigne de température interieure
 */
float consigne(float thermostatPrec_f)
{
    // Tentative de lecture de consigne.txt

    // Si le fichier .verrouConsigne existe, le fichier consigne.txt est en 
    // cours d'utilisation par un autre programme, retour de la fonction.
    if (access(".verrouConsigne", F_OK) != -1)
    {
        // printf("Impossible d'ouvrir consigne.txt, le fichier est en cours d'utilisation.\n");
        return thermostatPrec_f;
    }
    // Sinon, création d'un fichier .verrouConsigne qui indique que le fichier
    // consigne.txt est en cours de lecture par ce programme.
    else
    {
        FILE *fp2 = fopen(".verrouConsigne", "w");
        fclose(fp2);
    }

    // Lecture du fichier consigne.txt
    FILE *fp = fopen("consigne.txt", "r");

    // Si le fichier consigne.txt n'existe pas, on quitte le programme.
    if (fp == NULL)
    {
        printf("Impossible d'ouvrir consigne.txt, le programme va se fermer \n");
        exit(1);
    }

    float thermostat_f = 0; // Consigne de température

    // Lecture de la consigne de température dans le fichier consigne.txt
    fscanf(fp, "%f", &thermostat_f);
    fclose(fp); // Fermeture du fichier consigne.txt après lecture

    // Suppression du fichier .verrouConsigne après manipulation du fichier
    // consigne.txt
    remove(".verrouConsigne");

    // Retourne la consigne de température
    return thermostat_f;
}
