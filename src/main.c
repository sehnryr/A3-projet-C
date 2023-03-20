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
    printf("----- Auto tests results: -----\n");
    printf("testVisualisationT\t: score = %g%%\n", score1 * 100);
    printf("testConsigne \t\t: score = %g%%\n", score2 * 100);
    printf("testVisualisationC\t: score = %g%%\n", score3 * 100);
    printf("testRegulationTOR\t: score = %g%%\n", score4 * 100);
    printf("testRegulationPID\t: score = %g%%\n", score5 * 100);
    return EXIT_SUCCESS;
}
