#include "releve.h"

/**
 * @brief Releve la temperature via la liaison USB
 *
 * @param ftHandle Le handle de la liaison USB
 * @return temp_t La temperature interieure et exterieure relevee
 */
temp_t releve(FT_HANDLE ftHandle)
{
    // TODO: Implementer la fonction

    // je reprends l'exemple de la page 17 de la doc et je modifie les valeurs pour que ca fonctionne
    // j'suis pas sur de tt comprendre le code et j'peux pas test donc bon, 'jfais de mon mieux

    FT_STATUS ftStatus;
    DWORD RxBytes;
    DWORD TxBytes;
    DWORD BytesReceived;
    char RxBuffer[256];
    DWORD EventDWord;
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

    while (1) // je boucle a l'infini
    {
        FT_SetTimeouts(ftHandle, 100000, 0); // toutles les 100sec

        FT_GetStatus(ftHandle, &RxBytes, &TxBytes, &EventDWord); // je vois si j'ai recu qqch
        if (RxBytes > 0)                                         // si j'ai reçu
        {
            ftStatus = FT_Read(ftHandle, RxBuffer, RxBytes, &BytesReceived); // je lis
            if (ftStatus == FT_OK)
            {
                if (BytesReceived == RxBytes)
                {
                    // FT_Read OK
                    // je recuperer les valeurs de temp interieure stockée dans les 4 derniers bit des 3 premier octets


                
                }
                else
                {
                    // FT_Read Timeout
                }
            }
            else
            {
                // FT_Read Failed
            }
        }
    }

    FT_Close(ftHandle);
}