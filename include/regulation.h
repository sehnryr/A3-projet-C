#include <stdio.h>
#include <stdlib.h>
#include "define.h"

#ifndef REGULATION_H
#define REGULATION_H

#define DELTA_T 10.0 // Durée d'un pas de régulation en secondes

#define Kp 1.1
#define Ki 0.2
#define Kd 0.15

/// Ancienne valeur de l'écart
static float old_e = 0;

/// Ancienne valeur de la commande
static float old_cmd = 0;

/// Terme intégral de la régulation PID
static float I = 0;

/// Type d'une consigne
enum REGULATION_TYPE
{
    TOUT_OU_RIEN = 1, /// Tout ou rien
    PID = 2           /// Proportionnel Intégral Dérivé
};

float regulation(int regul, float temp, float consigne);
float regulationTest(int regul, float consigne, float *tabT, int nT);

#endif // REGULATION_H