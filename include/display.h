#ifndef DISPLAY_H
#define DISPLAY_H

#include "structures.h"

void displayStudent(Student* student, int details);

void displayProm(Prom* prom, int details);

void displayFirstStudents(Prom* prom, int n, int details);

void displayStudentById(Prom* prom, int id, int details);

void displayStudentByName(Prom* prom, char* firstname, char* lastname, int details);

void displayTop10(Student* topStudents, int size);

void displayTop3InCourse(Student* top3, char* courseName);

void API_display_results_per_field(CLASS_DATA* classData);

#endif /* DISPLAY_H */
