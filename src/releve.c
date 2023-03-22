/**
 * @file releve.c
 * @brief Fonction de releve de la temperature via la liaison USB
 * @authors
 * - Alexandre Auguste <alexandre.auguste@isen-ouest.yncrea.fr>
 * @date 2023-03-20
 */

#include "releve.h"

FT_STATUS releve(FT_HANDLE ftHandle, temp_t *temp)
{
    FT_STATUS ftStatus;
    DWORD RxBytes;
    DWORD TxBytes;
    DWORD BytesReceived;
    DWORD EventDWord;
    unsigned int SOT_ext = 0;
    unsigned int SOT_int = 0;

    // Vérification de la disponibilité de données
    ftStatus = FT_GetStatus(ftHandle, &RxBytes, &TxBytes, &EventDWord);

    // Si des données sont disponibles à la lecture
    if (ftStatus == FT_OK && RxBytes > 0)
    {
        // Allocation de la mémoire pour les données à lire
        char *RxBuffer = (char *)malloc(RxBytes * sizeof(char));

        // Lecture des données
        ftStatus = FT_Read(ftHandle, RxBuffer, RxBytes, &BytesReceived);

        if (ftStatus == FT_OK)
        {
            unsigned char octets_lus = 0;

            // FT_Read OK
            for (unsigned int i = 0; i < (unsigned int)BytesReceived; i++)
            {
                switch ((RxBuffer[i] & 0xF0) >> 4)
                {
                case 0b0000: // 1er octet de la température extérieur
                    SOT_ext |= (RxBuffer[i] & 0xF);
                    octets_lus += 1;
                    break;

                case 0b0001: // 2eme octet de la température extérieur
                    SOT_ext |= (RxBuffer[i] & 0xF) << 4;
                    octets_lus += 1;
                    break;

                case 0b0100: // 3eme octet de la température extérieur
                    SOT_ext |= (RxBuffer[i] & 0xF) << 8;
                    octets_lus += 1;
                    break;

                case 0b1000: // 1er octet de la température intérieur
                    SOT_int |= (RxBuffer[i] & 0xF);
                    octets_lus += 1;
                    break;

                case 0b1001: // 2eme octet de la température intérieur
                    SOT_int |= (RxBuffer[i] & 0xF) << 4;
                    octets_lus += 1;
                    break;

                case 0b1100: // 3eme octet de la température intérieur
                    SOT_int |= (RxBuffer[i] & 0xF) << 8;
                    octets_lus += 1;
                    break;

                default:
                    break;
                }
            }

            // Calcul de la température absolue en °C
            float temp_ext_absolu = -39.64 + 0.04 * (SOT_ext);
            float temp_int_absolu = -39.64 + 0.04 * (SOT_int);

            // Verification de la validité des données
            if (SOT_ext != 0 &&
                SOT_int != 0 &&
                temp_ext_absolu >= 0 &&
                temp_int_absolu >= 0 &&
                temp_ext_absolu <= 40 &&
                temp_int_absolu <= 40 &&
                octets_lus == 6)
            {
                // Si les données sont valides, on les enregistre
                temp->exterieure = temp_ext_absolu;
                temp->interieure = temp_int_absolu;
            }
        }
    }

    return ftStatus;
}
