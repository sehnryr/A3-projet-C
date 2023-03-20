#include <stdio.h>
#include <stdlib.h>
#include "define.h"

#ifndef REGULATION_H
#define REGULATION_H

#define Kp 1.0
#define Ki 0.1
#define Kd 0.1

/// Type d'une consigne
enum REGULATION_TYPE
{
    TOUT_OU_RIEN = 1, /// Tout ou rien
    PID = 2           /// Proportionnel Intégral Dérivé
};

float regulation(int regul, float temp, float consigne);
float regulationTest(int regul, float consigne, float *tabT, int nT);

#endif // REGULATION_H