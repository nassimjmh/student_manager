#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include "structures.h"

int saveProm(Prom* prom, char* filename);

Prom* loadProm(char* filename);

#endif /* SAVE_LOAD_H */
