#include "commande.h"

/**
 * @brief Envoie la commande de chauffage via la liaison USB
 *
 * @param ftHandle Le handle de la liaison USB
 * @param puissance_f La consigne de chauffage
 */
void commande(FT_HANDLE ftHandle, float puissance_f)
{
    // TODO: Implementer la fonction
    float PUIS = (puissance_f / 127) * 100;

    // page 18 de la doc, je reprends la fonction en exemple

    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;
    DWORD BytesWritten;
    char TxBuffer[1]; // Contains data to write to device <- ici, on modifie que le premier bit en fonction de si on met le chauffage ou non
    ftStatus = FT_Open(0, &ftHandle);
    if (ftStatus != FT_OK)
    {
        // FT_Open failed
        return;
    }

    // doc page 19 exemple
    ftStatus = FT_SetBaudRate(ftHandle, 115200); // Set baud rate to 115200
    if (ftStatus == FT_OK)
    {
        // FT_SetBaudRate OK
    }
    else
    {
        // FT_SetBaudRate Failed
    }

    // doc page 20 exemple
    // Set 8 data bits, 1 stop bit and no parity
    ftStatus = FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE);
    if (ftStatus == FT_OK)
    {
        // FT_SetDataCharacteristics OK
    }
    else
    {
        // FT_SetDataCharacteristics Failed
    }

    // doc page 22 exemple, je remplace par FT_FLOW_RTS_CTS par FT_FLOW_NONE car on en demande pas
    ftStatus = FT_SetFlowControl(ftHandle, FT_FLOW_NONE, 0x11, 0x13);
    if (ftStatus == FT_OK)
    {
        // FT_SetFlowControl OK
    }
    else
    {
        // FT_SetFlowControl Failed
    }

    if (PUIS > 0)
    {
        // définition du bit 7 à 1
        TxBuffer[0] = 0x80; // 0x80 = 1000 0000
        // définition des bits 6 à 0 à la valeur de la puissance en gardant le bit 7 à 1
        TxBuffer[0] = TxBuffer[0] | ((int)PUIS & 0x7F); // 0x7F = 0111 1111, cela me permet de garder les 7 bits de poids faible de PUIS, jsp si je peux cast en int comme ca et le balancer dans le truc, mais j'verrais bien si ca fonctionne quand je ferai le test
    }
    else
    {
        TxBuffer[0] = 0x00;
    }

    ftStatus = FT_Write(ftHandle, TxBuffer, sizeof(TxBuffer), &BytesWritten);

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
