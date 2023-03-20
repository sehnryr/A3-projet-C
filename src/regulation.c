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
        // on allume le chauffage à 50%. Sinon, on l'éteint.
        if (temp < consigne)
            return 50;
        else
            return 0;
    case PID:;
        // Ecart entre la consigne et la température
        float e = consigne - temp;

        // Terme proportionnel
        float P = Kp * e;

        // Si la consigne a changé, on réinitialise les termes intégral et dérivé
        if (consigne != old_cmd)
        {
            I = 0;
            old_e = e;
            old_cmd = consigne;
        }
        else
        {
            // Terme intégral
            I += Ki * old_e * DELTA_T / 2;
            I += Ki * e * DELTA_T / 2;
        }

        // Terme dérivé
        float D = Kd * (e - old_e) / DELTA_T;
        old_e = e;

        // printf("P = %f, I = %f, D = %f (e = %f, temp = %f, consigne = %f)\n", P, I, D, e, temp, consigne);

        // Commande
        float cmd = P + I + D;

        return cmd > 0 ? cmd <= 100 ? cmd : 100 : 0;
    default:
        return 0;
    }
}

float regulationTest(int regul, float consigne, float *tabT, int nT)
{
    float cmd = 100.0;

    old_e = 0;
    old_cmd = 0;
    I = 0;

    for (int i = 0; i < nT; ++i)
    {
        cmd = regulation(regul, tabT[i], consigne);
    }

    return cmd;
}
