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

    while (1) // je boucle a l'infini
    {
        FT_SetTimeouts(ftHandle, 100000, 0); // toutles les 100sec

        FT_GetStatus(ftHandle, &RxBytes, &TxBytes, &EventDWord); // je vois si j'ai recu qqch
        if (RxBytes > 0)                                         // si j'ai reçu
        {
            ftStatus = FT_Read(ftHandle, RxBuffer, RxBytes, &BytesReceived); // je lis
            if (ftStatus == FT_OK)
            {
                // FT_Read OK
            }
            else
            {
                // FT_Read Failed
            }
        }
    }

    FT_Close(ftHandle);
}