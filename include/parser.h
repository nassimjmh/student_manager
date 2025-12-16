#ifndef PARSER_H
#define PARSER_H

#include "structures.h"

Student parseStudentLine(char* line);

Course parseCourseLine(char* line);

void parseAndAddGrade(char* line, Prom* prom);

void updateCourseAverage(Course* course);

void updateStudentAverage(Student* student);

Student* findStudentById(Prom* prom, int id);

Student* findStudentByName(Prom* prom, char* firstname, char* lastname);

Course* findCourseByName(Student* student, char* courseName);

Prom* loadFile(char* filename);

#endif /* PARSER_H */
