/**
 * @file regulation.h
 * @brief Fonction de régulation de la température intérieure
 * @authors
 * - Youn Mélois <youn@melois.dev>
 * @date 2023-03-20
 */

#include <stdio.h>
#include <stdlib.h>
#include "define.h"

#ifndef REGULATION_H
#define REGULATION_H

#define DELTA_T 10.0 ///< Durée d'un pas de régulation en secondes

#define Kp 1.1  ///< Coefficient du terme proportionnel du PID
#define Ki 0.2  ///< Coefficient du terme intégral du PID
#define Kd 0.15 ///< Coefficient du terme dérivé du PID

/// @brief Type d'une consigne
enum REGULATION_TYPE
{
    TOUT_OU_RIEN = 1, ///< Tout ou rien
    PID = 2           ///< Proportionnel Intégral Dérivé
};

/**
 * @brief Fonction de régulation
 *
 * @param regul Type de régulation
 * @param temperature Température intérieure
 * @param consigne Consigne de température intérieure à atteindre
 * @param ancien_consigne Ancienne consigne
 * @param ancien_ecart Ancien écart
 * @param I Terme intégral
 * @return Commande de chauffage
 */
float regulation(
    int regul,
    float temperature,
    float consigne,
    float *ancien_consigne,
    float *ancien_ecart,
    float *pPID_I);

/**
 * @brief Fonction de test de la régulation
 *
 * @param regul Type de régulation
 * @param consigne Consigne de température intérieure à atteindre
 * @param tabT Tableau des températures intérieures
 * @param nT Nombre de températures intérieures
 */
float regulationTest(int regul, float consigne, float *tabT, int nT);

#endif // REGULATION_H