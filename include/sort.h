#ifndef SORT_H
#define SORT_H

#include "structures.h"

#define SIZE_TOP1 10

char** getTopStudents(Prom* prom, int n);

char** getTopInCourse(Prom* prom, char* courseName, int n);

// Change le mode de tri (Nom, Prénom, Moyenne, ou Note Min)
int API_set_sorting_mode(CLASS_DATA* pClass, int mode);

// Trie les étudiants selon le mode choisi
char** API_sort_students(CLASS_DATA* pClass);

#endif /* SORT_H */
