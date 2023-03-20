#include <stdio.h>
#include <stdlib.h>
#include "consigne.h"
#include "regulation.h"
#include "simulateur.h"
#include "visualisationC.h"
#include "visualisationT.h"

int main()
{
    // Températures initiales (valeurs par défaut du simulateur)
    temp_t temperature;
    temperature.exterieure = 10.0;
    temperature.interieure = 20.0;

    // Création du simulateur (puissance initialement à 0%)
    struct simParam_s *simulateur_ps = simConstruct(temperature);

    float thermostat = 0; // Consigne de température
    float puissance = 0;  // Puissance de chauffage

    // Régulation PID
    const int regul = PID;      // Type de régulation
    float PID_old_consigne = 0; // Ancienne consigne
    float PID_old_e = 0;        // Ancien écart
    float PID_I = 0;            // Terme intégral

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

        // Calcul de la température
        temperature = simCalc(puissance, simulateur_ps);

        // Visualisation de la consigne
        visualisationC(puissance);

        // Visualisation de la température
        visualisationT(temperature);
    }

    // Destruction du simulateur
    simDestruct(simulateur_ps);

    // Mise de la puissance à 0 pour arrêter le chauffage
    puissance = 0;
    visualisationC(puissance);

    return EXIT_SUCCESS;
}
