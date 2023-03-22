/**
 * @file commande.h
 * @brief Fonction de commande de chauffage via la liaison USB
 * @authors
 * - Alexandre Auguste <alexandre.auguste@isen-ouest.yncrea.fr>
 * @date 2023-03-20
 */

#include "ftd2xx.h"

#ifndef COMMANDE_H
#define COMMANDE_H

/**
 * @brief Envoie la commande de chauffage via la liaison USB
 *
 * @param ftHandle Le handle de la liaison USB
 * @param puissance_f La consigne de chauffage
 * @return Le status de la commande
 */
FT_STATUS commande(FT_HANDLE ftHandle, float puissance_f);

#endif // COMMANDE_H