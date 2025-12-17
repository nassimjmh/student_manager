#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/operations.h"


int miseAJourNotes(Prom* prom, Recalcul* pRecalcul){
    if (prom == NULL || pRecalcul == NULL) {
        return -1; 
    }
    if (pRecalcul->max>20 || pRecalcul->min<0)
    // Recherche de moyenne extremes
    for (int i = 0; i < prom->number; i++) {
        if(&prom->students->avg>&pRecalcul->max || &prom->students->avg<&pRecalcul->min){
            pRecalcul->func(&prom->students[i], pRecalcul->max, pRecalcul->min);
        }
    
    

    }
    return 1;
}