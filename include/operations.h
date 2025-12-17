#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "structures.h"

typedef void (*Recalcul)(Student* student, int max, int min);

typedef struct recalcul {
    Recalcul func;
    float max;
    float min;
} Recalcul;

int miseAJourNotes(Prom* prom, Recalcul* pRecalcul);

#endif /* OPERATIONS_H */