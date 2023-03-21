/**
 * @file test_autotests.c
 * @brief Programme de test des fonctions de l'application
 * @authors
 * - Alexandre Auguste <alexandre.auguste@isen-ouest.yncrea.fr>
 * - Youn Mélois <youn@melois.dev>
 * @date 2023-03-20
 */

#include <stdio.h>
#include <stdlib.h>
#include "autotests.h"

int main()
{
    int score1, score2, score3, score4, score5 = 0;
    score1 = (int)(testVisualisationT() * 100);
    score2 = (int)(testConsigne()       * 100);
    score3 = (int)(testVisualisationC() * 100);
    score4 = (int)(testRegulationTOR()  * 100);
    score5 = (int)(testRegulationPID()  * 100);
    printf("------ Auto tests results: ------\n");
    printf("testVisualisationT : score = %3d%%\n", score1);
    printf("testConsigne       : score = %3d%%\n", score2);
    printf("testVisualisationC : score = %3d%%\n", score3);
    printf("testRegulationTOR  : score = %3d%%\n", score4);
    printf("testRegulationPID  : score = %3d%%\n", score5);

    if (score1 != 100 ||
        score2 != 100 ||
        score3 != 100 ||
        score4 != 100 ||
        score5 != 100)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
