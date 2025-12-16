#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/structures.h"

Grades* createGrades(float* data, int size) {
    if (data == NULL || size <= 0) {
        fprintf(stderr, "Error: Invalid parameters for createGrades\n");
        return NULL;
    }
    
    Grades* newGrades = malloc(sizeof(Grades));
    if (newGrades == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Grades\n");
        return NULL;
    }
    
    newGrades->data = malloc(size * sizeof(float));
    if (newGrades->data == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Grades data\n");
        free(newGrades);
        return NULL;
    }
    
    memcpy(newGrades->data, data, size * sizeof(float));
    newGrades->size = size;
    
    return newGrades;
}

Course* createCourse(float coef, float avg, char* name, Grades* grades) {
    if (name == NULL) {
        fprintf(stderr, "Error: Invalid course name\n");
        return NULL;
    }
    
    Course* newCourse = malloc(sizeof(Course));
    if (newCourse == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Course\n");
        return NULL;
    }
    
    newCourse->name = malloc(strlen(name) + 1);
    if (newCourse->name == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for course name\n");
        free(newCourse);
        return NULL;
    }
    
    strcpy(newCourse->name, name);
    newCourse->grades = grades;
    newCourse->coef = coef;
    newCourse->avg = avg;
    
    return newCourse;
}

Student* createStudent(int age, int id, int size, float avg, char* name, 
                      char* surname, Course* courses) {
    if (name == NULL || surname == NULL) {
        fprintf(stderr, "Error: Invalid student name\n");
        return NULL;
    }
    
    Student* newStudent = malloc(sizeof(Student));
    if (newStudent == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Student\n");
        return NULL;
    }
    
    newStudent->name = malloc(strlen(name) + 1);
    if (newStudent->name == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for student first name\n");
        free(newStudent);
        return NULL;
    }
    strcpy(newStudent->name, name);
    
    newStudent->surname = malloc(strlen(surname) + 1);
    if (newStudent->surname == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for student last name\n");
        free(newStudent->name);
        free(newStudent);
        return NULL;
    }
    strcpy(newStudent->surname, surname);
    
    newStudent->courses = courses;
    newStudent->age = age;
    newStudent->id = id;
    newStudent->size = size;
    newStudent->avg = avg;
    
    return newStudent;
}

Prom* createProm(Student* students, int number) {
    if (students == NULL || number <= 0) {
        fprintf(stderr, "Error: Invalid parameters for createProm\n");
        return NULL;
    }
    
    Prom* newProm = malloc(sizeof(Prom));
    if (newProm == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Prom\n");
        return NULL;
    }
    
    newProm->students = students;
    newProm->number = number;
    
    return newProm;
}

void destroyGrades(Grades* grades) {
    if (grades == NULL) {
        return;
    }
    
    if (grades->data != NULL) {
        free(grades->data);
    }
    free(grades);
}

void destroyCourse(Course* course) {
    if (course == NULL) {
        return;
    }
    
    if (course->name != NULL) {
        free(course->name);
    }
    
    if (course->grades != NULL) {
        destroyGrades(course->grades);
    }
    
    free(course);
}

void destroyStudentContent(Student* student) {
    if (student == NULL) {
        return;
    }
    
    if (student->name != NULL) {
        free(student->name);
    }
    
    if (student->surname != NULL) {
        free(student->surname);
    }
    
    if (student->courses != NULL) {
        for (int i = 0; i < student->size; i++) {
            if (student->courses[i].name != NULL) {
                free(student->courses[i].name);
            }
            if (student->courses[i].grades != NULL) {
                destroyGrades(student->courses[i].grades);
            }
        }
        free(student->courses);
    }
}

void destroyProm(Prom* prom) {
    if (prom == NULL) {
        return;
    }
    
    if (prom->students != NULL) {
        for (int i = 0; i < prom->number; i++) {
            destroyStudentContent(&prom->students[i]);
        }
        free(prom->students);
    }
    
    free(prom);
}

int getCourseIndex(char* name) {
    if (strcmp(name, "Mathematiques") == 0) return MATHEMATIQUES;
    if (strcmp(name, "Physique") == 0) return PHYSIQUE;
    if (strcmp(name, "Informatique") == 0) return INFORMATIQUE;
    if (strcmp(name, "Chimie") == 0) return CHIMIE;
    if (strcmp(name, "Biologie") == 0) return BIOLOGIE;
    if (strcmp(name, "Histoire") == 0) return HISTOIRE;
    if (strcmp(name, "Geographie") == 0) return GEOGRAPHIE;
    if (strcmp(name, "Français") == 0 || strcmp(name, "Francais") == 0) return FRANCAIS;
    if (strcmp(name, "Anglais") == 0) return ANGLAIS;
    if (strcmp(name, "EPS") == 0) return EPS;
    if (strcmp(name, "Philosophie") == 0) return PHILOSOPHIE;
    if (strcmp(name, "Economie") == 0) return ECONOMIE;
    if (strcmp(name, "Sociologie") == 0) return SOCIOLOGIE;
    if (strcmp(name, "Arts Plastiques") == 0) return ARTS_PLASTIQUES;
    if (strcmp(name, "Musique") == 0) return MUSIQUE;
    if (strcmp(name, "Technologie") == 0) return TECHNOLOGIE;
    if (strcmp(name, "Latin") == 0) return LATIN;
    if (strcmp(name, "Espagnol") == 0) return ESPAGNOL;
    if (strcmp(name, "Allemand") == 0) return ALLEMAND;
    if (strcmp(name, "Sciences Sociales") == 0) return SCIENCES_SOCIALES;
    
    return -1; // Introuvable
}

// Fonction pour mettre à jour les flags d'un étudiant
void updateStudentValidation(Student* s) {
    if (s == NULL) return;

    // 1. On remet tout à zéro pour être propre
    s->validation_flags = 0;

    // 2. On parcourt ses matières
    for (int i = 0; i < s->size; i++) {
        Course* c = &s->courses[i];
        
        // On récupère l'index correspondant au nom (ex: "Maths" -> 0)
        int index = getCourseIndex(c->name);

        // Si la matière est connue ET que la moyenne >= 10.0
        if (index != -1 && c->avg >= 10.0) {
            // OPÉRATION BINAIRE : On allume le bit correspondant
            // |= signifie "Ajoute ce bit aux bits existants"
            s->validation_flags |= (1ULL << index);
        }
    }
}