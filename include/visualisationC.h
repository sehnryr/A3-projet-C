/**
 * @file visualisationC.h
 * @brief Fonction de visualisation de la consigne de chauffage
 * @authors
 * - Alexandre Auguste <alexandre.auguste@isen-ouest.yncrea.fr>
 * @date 2023-03-20
 */

#include <string.h>
#include "define.h"

#ifndef VISUALISATIONC_H
#define VISUALISATIONC_H

/**
 * @brief Envoi d'un témoin de chauffe à la visualisation
 *
 * @param puissance_f Puissance de chauffage
 */
void visualisationC(float puissance_f);

#endif // VISUALISATIONC_H