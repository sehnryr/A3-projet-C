/**
 * @file commande.c
 * @brief Fonction de commande de chauffage via la liaison USB
 * @authors
 * - Alexandre Auguste <alexandre.auguste@isen-ouest.yncrea.fr>
 * @date 2023-03-20
 */

#include "commande.h"

void commande(FT_HANDLE ftHandle, float puissance_f)
{
    // TODO: Implementer la fonction
    int PUIS = (puissance_f / 100) * 127;

    // page 18 de la doc, je reprends la fonction en exemple

    FT_STATUS ftStatus;
    DWORD BytesWritten;
    char TxBuffer[1]; // Contains data to write to device

    if (PUIS > 0)
    {
        // définition du bit 7 à 1
        // TxBuffer[0] = 0x80; // 0x80 = 1000 0000 <- y'a un overflow ici
        // définition des bits 6 à 0 à la valeur de la puissance en gardant le bit 7 à 1
        TxBuffer[0] = 0x80 | (PUIS & 0x7F); // 0x7F = 0111 1111, cela me permet de garder les 7 bits de poids faible de PUIS, jsp si je peux cast en int comme ca et le balancer dans le truc, mais j'verrais bien si ca fonctionne quand je ferai le test
    }
    else
    {
        TxBuffer[0] = 0x00;
    }

    ftStatus = FT_Write(ftHandle, TxBuffer, sizeof(TxBuffer), &BytesWritten); // Write data to device

    if (ftStatus == FT_OK)
    {
        // FT_Write OK
    }
    else
    {
        // FT_Write Failed
    }
    FT_Close(ftHandle);
}
