/**
 * @file define.h
 * @brief Définition des structures de données
 * @date 2023-03-20
 */

#ifndef DEFINE_H
#define DEFINE_H

#include <stdio.h>
#include <stdlib.h>

/// @brief Structure de données pour la température
typedef struct
{
    float interieure; ///< Température intérieure
    float exterieure; ///< Température extérieure
} temp_t;

#endif