#include <stdio.h>
#include <string.h>
#include "../include/display.h"
#include "../include/parser.h"

void displayStudent(Student* student) {
    if (student == NULL) {
        fprintf(stderr, "Error: Cannot display NULL student\n");
        return;
    }
    
    printf("Name: %s %s   ", student->name, student->surname);
    printf("Overall Average: %.2f/20\n", student->avg);
    printf("\nCourses:\n");
    
    for (int i = 0; i < student->size; i++) {
        Course* c = &student->courses[i];
        printf("  - %s (coef %.2f): ", c->name, c->coef);
        
        if (c->grades == NULL || c->grades->size == 0) {
            printf("No grades\n");
        } else {
            printf("Average %.2f/20 (", c->avg);
            for (int j = 0; j < c->grades->size; j++) {
                printf("%.1f", c->grades->data[j]);
                if (j < c->grades->size - 1) printf(", ");
            }
            printf(")\n");
        }
    }
}

void displayProm(Prom* prom) {
    if (prom == NULL) {
        fprintf(stderr, "Error: Cannot display NULL cohort\n");
        return;
    }
    
    printf("\n######################################\n");
    printf("COHORT - %d students\n", prom->number);
    printf("######################################\n");
    
    for (int i = 0; i < prom->number; i++) {
        displayStudent(&prom->students[i]);
    }
}

void displayFirstStudents(Prom* prom, int n) {
    if (prom == NULL) {
        fprintf(stderr, "Error: Cannot display NULL cohort\n");
        return;
    }
    
    printf("\n DISPLAYING FIRST %d STUDENTS \n", n);
    
    for (int i = 0; i < n && i < prom->number; i++) {
        displayStudent(&prom->students[i]);
    }
}

void displayStudentById(Prom* prom, int id) {
    if (prom == NULL) {
        fprintf(stderr, "Error: Cannot display from NULL cohort\n");
        return;
    }
    
    Student* student = findStudentById(prom, id);
    
    if (student == NULL) {
        printf("Error: Student with ID %d not found\n", id);
        return;
    }
    
    displayStudent(student);
}

void displayStudentByName(Prom* prom, char* firstname, char* lastname) {
    if (prom == NULL || firstname == NULL || lastname == NULL) {
        fprintf(stderr, "Error: Invalid parameters\n");
        return;
    }
    
    Student* student = findStudentByName(prom, firstname, lastname);
    
    if (student == NULL) {
        printf("Error: Student %s %s not found\n", firstname, lastname);
        return;
    }
    
    displayStudent(student);
}

void displayTop10(Student* topStudents, int size) {
    if (topStudents == NULL || size <= 0) {
        fprintf(stderr, "Error: Invalid parameters\n");
        return;
    }
    
    printf("\n=== TOP %d STUDENTS ===\n", size);
    for (int i = 0; i < size; i++) {
        printf("%d. %s %s - Average: %.2f/20\n", 
               i + 1, 
               topStudents[i].name, 
               topStudents[i].surname, 
               topStudents[i].avg);
    }
}

void displayTop3InCourse(Student* top3, char* courseName) {
    if (top3 == NULL || courseName == NULL) {
        fprintf(stderr, "Error: Invalid parameters\n");
        return;
    }
    
    printf("\n=== TOP 3 IN %s ===\n", courseName);
    for (int i = 0; i < 3; i++) {
        if (top3[i].id == -1) break;
        
        Course* course = findCourseByName(&top3[i], courseName);
        if (course != NULL) {
            printf("%d. %s %s - Average: %.2f/20\n", 
                   i + 1, 
                   top3[i].name, 
                   top3[i].surname, 
                   course->avg);
        }
    }
}


void API_display_results_per_field(CLASS_DATA* classData) {
    if (classData == NULL || classData->prom == NULL) return;

    printf("\n=== RÉSULTATS VALIDATION PAR PÔLES ===\n");
    
    for (int i = 0; i < classData->prom->number; i++) {
        Student* s = &classData->prom->students[i];
        
        printf("%-15s %-15s : ", s->surname, s->name);
        
        // 1. Test Sciences
        // On utilise l'opérateur bit-à-bit '&'
        int scienceValide = ((s->validation_flags & SCIENCES_MASK) == SCIENCES_MASK);
        if (scienceValide) {
            printf("[SCIE: OK] ");
        } else {
            printf("[SCIE: --] ");
        }
        
        // 2. Test Humanités
        int humaniteValide = ((s->validation_flags & HUMANITIES_MASK) == HUMANITIES_MASK);
        if (humaniteValide) {
            printf("[HUMA: OK] ");
        } else {
            printf("[HUMA: --] ");
        }
        
        // 3. Test Année Complète (Question 5)
        // Si tout est validé (YEAR_MASK)
        if ((s->validation_flags & YEAR_MASK) == YEAR_MASK) {
            printf("=> ANNÉE VALIDÉE !");
        }
        
        printf("\n");
    }
}