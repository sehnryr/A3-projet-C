/**
 * @file releve.h
 * @brief Fonction de releve de la temperature via la liaison USB
 * @authors
 * - Alexandre Auguste <alexandre.auguste@isen-ouest.yncrea.fr>
 * @date 2023-03-20
 */

#include "ftd2xx.h"
#include "define.h"

#ifndef RELEVE_H
#define RELEVE_H

/**
 * @brief Releve la temperature via la liaison USB
 *
 * @param ftHandle Le handle de la liaison USB
 * @param ancien_temp_ext temperature exterieure lorsqu'on appelle la fct
 * @param ancien_temp_int temperature interieure lorsqu'on appelle la fct
 * @return temp_t La temperature interieure et exterieure relevee
 */
temp_t releve(FT_HANDLE ftHandle, float ancien_temp_ext, float ancien_temp_int);

#endif // RELEVE_H