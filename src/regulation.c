/**
 * @file regulation.c
 * @brief Fonction de régulation de la température intérieure
 * @authors
 * - Youn Mélois <youn@melois.dev>
 * @date 2023-03-20
 */

#include <stdio.h>
#include <stdlib.h>
#include "regulation.h"

float regulation(
    enum REGULATION_TYPE regul,
    float temperature,
    float consigne,
    float *ancien_consigne,
    float *ancien_ecart,
    float *pPID_I)
{
    switch (regul)
    {
    case TOUT_OU_RIEN:
        // Si la température est inférieure à la consigne,
        // on allume le chauffage à 50%. Sinon, on l'éteint.
        return temperature < consigne ? 50 : 0;
    case PID:;
        // Ecart entre la consigne et la température
        float ecart = consigne - temperature;

        // Terme proportionnel
        float PID_P = Kp * ecart;

        // Terme intégral
        float PID_I = *pPID_I;
        PID_I += Ki * *ancien_ecart * DELTA_T / 2; // Première moitié du trapèze
        PID_I += Ki * ecart * DELTA_T / 2;         // Deuxième moitié du trapèze

        // Terme dérivé
        float PID_D = Kd * (ecart - *ancien_ecart) / DELTA_T;

        // Si la consigne a changé,
        // on réinitialise les termes intégral et dérivé
        if (consigne != *ancien_consigne)
        {
            PID_I = 0;
            PID_D = 0;
        }

        // Commande de chauffage
        float commande = PID_P + PID_I + PID_D;

        // Mise à jour des pointeurs
        *pPID_I = PID_I;
        *ancien_ecart = ecart;
        *ancien_consigne = consigne;

        // On s'assure que la commande est comprise entre 0 et 100
        return commande > 0 ? (commande <= 100 ? commande : 100) : 0;
    default:
        return 0;
    }
}

float regulationTest(int regul, float consigne, float *tabT, int nT)
{
    float cmd = 100.0;

    // Ancienne valeur de la commande
    float ancien_consigne = 0;

    // Ancienne valeur de l'écart
    float ancien_ecart = 0;

    // Terme intégral de la régulation PID
    float PID_I = 0;

    for (int i = 0; i < nT; ++i)
    {
        cmd = regulation(
            regul,
            tabT[i],
            consigne,
            &ancien_consigne,
            &ancien_ecart,
            &PID_I);
    }

    return cmd;
}
