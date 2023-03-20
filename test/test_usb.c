#include <stdlib.h>

#include "consigne.h"
#include "regulation.h"
#include "visualisationC.h"
#include "visualisationT.h"

#include "ftd2xx.h"
#include "commande.h"
#include "releve.h"

int main()
{
    // Températures initiales
    temp_t temperature;
    temperature.exterieure = 10.0;
    temperature.interieure = 20.0;

    float thermostat = 0; // Consigne de température
    float puissance = 0;  // Puissance de chauffage

    // Régulation PID
    const int regul = PID;      // Type de régulation
    float PID_old_consigne = 0; // Ancienne consigne
    float PID_old_e = 0;        // Ancien écart
    float PID_I = 0;            // Terme intégral

    // Initialisation de la communication USB
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;
    ftStatus = FT_Open(0, &ftHandle); // Might use FT_OpenEx() instead
    ftStatus = FT_SetBaudRate(ftHandle, FT_BAUD_115200);
    ftStatus = FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE);
    ftStatus = FT_SetFlowControl(ftHandle, FT_FLOW_NONE, 0, 0);

    // Vérification de l'initialisation
    if (ftStatus != FT_OK)
    {
        printf("Erreur d'initialisation de la communication USB !\n");
        return EXIT_FAILURE;
    }

    // Boucle de régulation
    while (1)
    {
        // Récupération de la consigne
        thermostat = consigne(thermostat);

        if (thermostat <= 5)
        {
            break;
        }

        // Régulation PID
        puissance = regulation(
            regul,
            temperature.interieure,
            thermostat,
            &PID_old_consigne,
            &PID_old_e,
            &PID_I);

        // TODO: Envoi de la puissance au chauffage

        // TODO: Récupération de la température

        // Visualisation de la consigne
        visualisationC(puissance);

        // Visualisation de la température
        visualisationT(temperature);
    }

    // Mise de la puissance à 0 pour arrêter le chauffage
    puissance = 0;
    visualisationC(puissance);
    // TODO: Envoi de la puissance au chauffage

    return EXIT_SUCCESS;
}
