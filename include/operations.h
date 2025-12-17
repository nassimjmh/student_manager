#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "structures.h"

typedef void (*Recalcul)(Student* student, int max, int min);

typedef struct recalcul {
    Recalcul func;
    float max;
    float min;
} Recalcul_data;

int miseAJourNotes(Prom* prom, Recalcul_data* pRecalcul);

Recalcul normalisation (Student* student, float max, float min);


#endif /* OPERATIONS_H */