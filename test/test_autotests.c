#include <stdio.h>
#include <stdlib.h>
#include "autotests.h"

int main()
{
    float score1, score2, score3, score4, score5 = 0;
    score1 = testVisualisationT();
    score2 = testConsigne();
    score3 = testVisualisationC();
    score4 = testRegulationTOR();
    score5 = testRegulationPID();
    printf("------ Auto tests results: ------\n");
    printf("testVisualisationT : score = %3g%%\n", score1 * 100);
    printf("testConsigne       : score = %3g%%\n", score2 * 100);
    printf("testVisualisationC : score = %3g%%\n", score3 * 100);
    printf("testRegulationTOR  : score = %3g%%\n", score4 * 100);
    printf("testRegulationPID  : score = %3g%%\n", score5 * 100);
    return EXIT_SUCCESS;
}
