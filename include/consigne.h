/**
 * @file consigne.h
 * @brief Fonction de récupération de la consigne de température
 * @authors
 * - Alexandre Auguste <alexandre.auguste@isen-ouest.yncrea.fr>
 * @date 2023-03-20
 */

#include <stdio.h>
#include <stdlib.h>
#include "define.h"

#ifndef CONSIGNE_H
#define CONSIGNE_H

/**
 * @brief Récupère la consigne de température
 *
 * @param thermostatPrec_f Ancienne consigne
 * @return Consigne de température interieure
 */
float consigne(float thermostatPrec_f);

#endif // CONSIGNE_H