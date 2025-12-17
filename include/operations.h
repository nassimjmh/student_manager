#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "structures.h"

typedef void (*Recalcul)(Student* student, float max, float min);

typedef struct recalcul {
    Recalcul func;
    float max;
    float min;
} Recalcul_data;

int miseAJourNotes(Prom* prom, Recalcul_data* pRecalcul);

void normalisation (Student* student, float max, float min);

char** listePrenoms(Prom* prom, int* taille);


#endif /* OPERATIONS_H */