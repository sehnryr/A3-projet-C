#include <stdio.h>
#include <stdlib.h>
#include "simulateur.h"

int main()
{
    // Températures initiales (valeurs par défaut du simulateur)
    temp_t temperature;
    temperature.exterieure = 10.0;
    temperature.interieure = 20.0;

    // Création du simulateur (puissance initialement à 0%)
    struct simParam_s *simulateur_ps = simConstruct(temperature);

    

    // Destruction du simulateur
    simDestruct(simulateur_ps);

    return EXIT_SUCCESS;
}
