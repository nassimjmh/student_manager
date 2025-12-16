#ifndef DISPLAY_H
#define DISPLAY_H

#include "structures.h"

void displayStudent(Student* student);

void displayProm(Prom* prom);

void displayFirstStudents(Prom* prom, int n);

void displayStudentById(Prom* prom, int id);

void displayStudentByName(Prom* prom, char* firstname, char* lastname);

void displayTop10(Student* topStudents, int size);

void displayTop3InCourse(Student* top3, char* courseName);

void API_display_results_per_field(CLASS_DATA* classData);

#endif /* DISPLAY_H */
