/**
 * @file commande.c
 * @brief Fonction de commande de chauffage via la liaison USB
 * @authors
 * - Alexandre Auguste <alexandre.auguste@isen-ouest.yncrea.fr>
 * @date 2023-03-20
 */

#include "commande.h"

FT_STATUS commande(FT_HANDLE ftHandle, float puissance_f)
{
    // Calcul de la puissance arrondie à l'entier le plus proche
    unsigned short PUIS = puissance_f * 127 / 100 + 0.5;

    DWORD BytesWritten;
    char TxBuffer[1] = {0};

    if (PUIS != 0)
    {
        // MSB à 1 pour indiquer que la commande est une commande de chauffage
        TxBuffer[0] |= 0x80;

        // Ajout de la puissance de chauffage dans le buffer
        TxBuffer[0] |= (PUIS & 0x7F);
    }

    // Envoie de la commande de chauffage via la liaison USB
    return FT_Write(ftHandle, TxBuffer, sizeof(TxBuffer), &BytesWritten);
}
