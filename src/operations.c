#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


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
            pRecalcul->func(&prom->students[i], maxAvg, minAvg);
        }
    return 1;
}


void normalisation (Student* student, float max, float min){
    if (student == NULL) {
        return;
    }
    float oldAvg = student->avg;
    float newAvg = ((oldAvg - min) / (max - min)) * 20.0;
    student->avg = newAvg;
}


char** listePrenoms(Prom* prom, int* taille) {
    if (prom == NULL || taille == NULL) {
        return NULL;
    }

    *taille = prom->number;
    int totalLength = 0;

    for (int i = 0; i < prom->number; i++) {
        if (prom->students[i].name != NULL) {
            totalLength += strlen(prom->students[i].name) + 1; 
        } else {
            totalLength += 1; 
        }
    }

    char* block = malloc(totalLength * sizeof(char));
    if (block == NULL) {
        return NULL;
    }

    char** liste = malloc(prom->number * sizeof(char*));
    if (liste == NULL) {
        free(block);
        return NULL;
    }

    char* current = block;
    for (int i = 0; i < prom->number; i++) {
        liste[i] = current; 
        if (prom->students[i].name != NULL) {
            strcpy(current, prom->students[i].name);
            
            /*for (int j = 0; current[j]; j++) {
                current[j] = toupper((unsigned char)current[j]);
            }
            */
            current += strlen(current) + 1;
        } else {
            *current = '\0'; 
            current++;
        }
    }
    return liste;
}