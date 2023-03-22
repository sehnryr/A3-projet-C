/**
 * @file releve.c
 * @brief Fonction de releve de la temperature via la liaison USB
 * @authors
 * - Alexandre Auguste <alexandre.auguste@isen-ouest.yncrea.fr>
 * @date 2023-03-20
 */

#include "releve.h"

temp_t releve(FT_HANDLE ftHandle, float ancien_temp_ext, float ancien_temp_int)
{
    // TODO: Implementer la fonction

    // je reprends l'exemple de la page 17 de la doc et je modifie les valeurs pour que ca fonctionne
    // j'suis pas sur de tt comprendre le code et j'peux pas test donc bon, 'jfais de mon mieux

    FT_STATUS ftStatus;
    DWORD RxBytes;
    DWORD TxBytes;
    DWORD BytesReceived;
    char RxBuffer[6];
    DWORD EventDWord;
    temp_t temp;
    int temp_ext[3] = {0, 0, 0};
    int temp_int[3] = {0, 0, 0};
        FT_SetTimeouts(ftHandle, 100000, 0); // tout les les 100sec

        FT_GetStatus(ftHandle, &RxBytes, &TxBytes, &EventDWord); // je vois si j'ai recu qqch
        if (RxBytes > 0)                                         // si j'ai reçu
        {
            ftStatus = FT_Read(ftHandle, RxBuffer, RxBytes, &BytesReceived); // je lis
            if (ftStatus == FT_OK)
            {
                // FT_Read OK
                for(int i =0; i < BytesReceived; i ++)
                {
                    switch(RxBuffer[i] >> 4)
                    {
                        case 0000: // 1er octet de la température extérieur
                            temp_ext[0] = RxBuffer[i] & 00001111; // SOT 1er octet
                            break;
                        case 0001: // 2eme octet de la température extérieur
                            temp_ext[1] = RxBuffer[i] & 00001111; // SOT 2eme octet
                            break;
                        case 0100: // 3eme octet de la température extérieur
                            temp_ext[2] = RxBuffer[i] & 00001111; // SOT 3eme octet
                            break;
                        case 1000: // 1er octet de la température intérieur
                            temp_int[0] = RxBuffer[i] & 00001111; // SOT 1er octet
                            break;
                        case 1001: // 2eme octet de la température intérieur
                            temp_int[1] = RxBuffer[i] & 00001111; // SOT 2eme octet
                            break;
                        case 1100: // 3eme octet de la température intérieur
                            temp_int[2] = RxBuffer[i] & 00001111; // SOT 3eme octet
                            break;
                    }
                }
                float SOT_temp_ext = temp_ext[0] << 4 | temp_ext[1] << 8 | temp_ext[2] << 12; // SOT température extérieur
                float SOT_temp_int = temp_int[0] << 4 | temp_int[1] << 8 | temp_int[2] << 12; // SOT température intérieur
                float temp_ext_absolu = -39.64  + 0.04 * (SOT_temp_ext); // température extérieur absolue
                float temp_int_absolu = -39.64  + 0.04 * (SOT_temp_int); // température intérieur absolue 
                temp.exterieure = temp_ext_absolu;
                temp.interieure = temp_int_absolu;
                return temp;
                
            }
            else
            {
                // FT_Read Failed
                temp.exterieure = ancien_temp_ext;
                temp.interieure = ancien_temp_int;
                return temp;
            }
        }
}