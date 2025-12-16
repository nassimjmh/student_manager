#ifndef SORT_H
#define SORT_H

#include "structures.h"

#define SIZE_TOP1 10

Student* getTop10Students(Prom* prom, int* resultSize);

Student* getTop3InCourse(Prom* prom, char* courseName);

int compareByAverage(const void* a, const void* b);

// Change le mode de tri (Nom, Prénom, Moyenne, ou Note Min)
int API_set_sorting_mode(CLASS_DATA* pClass, int mode);

// Trie les étudiants selon le mode choisi
char** API_sort_students(CLASS_DATA* pClass);

#endif /* SORT_H */
