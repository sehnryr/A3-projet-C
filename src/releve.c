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
    FT_STATUS ftStatus;
    DWORD RxBytes;
    DWORD TxBytes;
    DWORD BytesReceived;
    char RxBuffer[6];
    DWORD EventDWord;
    temp_t temp;
    temp.exterieure = ancien_temp_ext;
    temp.interieure = ancien_temp_int;
    unsigned int SOT_ext = 0;
    unsigned int SOT_int = 0;

    FT_GetStatus(ftHandle, &RxBytes, &TxBytes, &EventDWord); // je vois si j'ai recu qqch
    if (RxBytes > 0)                                         // si j'ai reçu
    {
        ftStatus = FT_Read(ftHandle, RxBuffer, RxBytes, &BytesReceived); // je lis
        if (ftStatus == FT_OK)
        {
            // FT_Read OK
            for (int i = 0; i < BytesReceived; i++)
            {
                switch ((RxBuffer[i] & 0xF0) >> 4)
                {
                case 0b0000:                        // 1er octet de la température extérieur
                    SOT_ext |= (RxBuffer[i] & 0xF); // SOT 1er octet
                    break;
                case 0b0001:                             // 2eme octet de la température extérieur
                    SOT_ext |= (RxBuffer[i] & 0xF) << 4; // SOT 2eme octet
                    break;
                case 0b0100:                             // 3eme octet de la température extérieur
                    SOT_ext |= (RxBuffer[i] & 0xF) << 8; // SOT 3eme octet
                    break;
                case 0b1000:                        // 1er octet de la température intérieur
                    SOT_int |= (RxBuffer[i] & 0xF); // SOT 1er octet
                    break;
                case 0b1001:                             // 2eme octet de la température intérieur
                    SOT_int |= (RxBuffer[i] & 0xF) << 4; // SOT 2eme octet
                    break;
                case 0b1100:                             // 3eme octet de la température intérieur
                    SOT_int |= (RxBuffer[i] & 0xF) << 8; // SOT 3eme octet
                    break;
                default:
                    break;
                }
            }
            float temp_ext_absolu = -39.64 + 0.04 * (SOT_ext); // température extérieur absolue
            float temp_int_absolu = -39.64 + 0.04 * (SOT_int); // température intérieur absolue
            temp.exterieure = temp_ext_absolu;
            temp.interieure = temp_int_absolu;
            return temp;
        }
    }

    return temp;
}
