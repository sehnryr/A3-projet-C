#include <stdio.h>
#include <stdlib.h>
#include "regulation.h"

/**
 * @brief Fonction de régulation
 *
 * @param regul Type de régulation
 * @param temp Température intérieure
 * @param consigne Consigne de température intérieure à atteindre
 */
float regulation(int regul, float temp, float consigne)
{
    switch (regul)
    {
    case TOUT_OU_RIEN:
        // Si la température est inférieure à la consigne,
        // on allume le chauffage à 40%. Sinon, on l'éteint.
        if (temp < consigne)
            return 0.4;
        else
            return 0;
    case PID:
        /* TODO: Implémentation PID */
    default:
        return 0;
    }
}

float regulationTest(int regul, float consigne, float *tabT, int nT)
{
    float cmd = 100.0;

    for (int i = 0; i < nT; ++i)
    {
        cmd = regulation(regul, tabT[i], consigne);
    }

    return cmd;
}
