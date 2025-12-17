#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/operations.h"


int miseAJourNotes(Prom* prom, Recalcul_data* pRecalcul){
    if (prom == NULL || pRecalcul == NULL) {
        return -1; 
    }
    // Recherche de moyenne extremes
    float minAvg = 20.0;
    float maxAvg = 0.0;
    for (int i = 0; i < prom->number; i++) {
        float avg = prom->students[i].avg;
        if (avg < minAvg) {
            minAvg = avg;
        }
        if (avg > maxAvg) {
            maxAvg = avg;
        }
    }
    pRecalcul->min = minAvg;
    pRecalcul->max = maxAvg;
    for (int i = 0; i < prom->number; i++) {
            pRecalcul->func(&prom->students[i], pRecalcul->max, pRecalcul->min);
        }
    return 1;
}


Recalcul normalisation (Student* student, float max, float min){
    // La plus petite moyenne se retrouve à 0, la plus grande se retrouve à 20. Les autres sont placées proportionnellement entre les 2
    if (student == NULL) {
        return;
    }
    for (int i = 0; i < student->size; i++) {
        float oldAvg = student->courses[i].avg;
        float newAvg = ((oldAvg - min) / (max - min)) * 20.0;
    }
}