/**
 * @file visualisationT.h
 * @brief Fonction d'envoi de la température à la visualisation
 * @authors
 * - Alexandre Auguste <alexandre.auguste@isen-ouest.yncrea.fr>
 * @date 2023-03-20
 */

#include <string.h>
#include "define.h"

#ifndef VISUALISATIONT_H
#define VISUALISATIONT_H

/**
 * @brief Envoi de la température à la visualisation
 *
 * @param myTemp Température intérieure et extérieure
 */
void visualisationT(temp_t myTemp);

#endif // VISUALISATIONT_H