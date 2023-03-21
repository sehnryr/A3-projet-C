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
 * @return temp_t La temperature interieure et exterieure relevee
 */
temp_t releve(FT_HANDLE ftHandle);

#endif // RELEVE_H