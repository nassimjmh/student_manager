#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/save_load.h"
#include "../include/structures.h"

int saveProm(Prom* prom, char* filename) {
    if (prom == NULL || filename == NULL) {
        fprintf(stderr, "Error: Invalid parameters for saveProm\n");
        return -1;
    }
    
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        fprintf(stderr, "Error: Cannot create file %s\n", filename);
        return -1;
    }
    
    fwrite(&prom->number, sizeof(int), 1, file);
    
    for (int i = 0; i < prom->number; i++) {
        Student* s = &prom->students[i];
        
        fwrite(&s->id, sizeof(int), 1, file);
        fwrite(&s->age, sizeof(int), 1, file);
        fwrite(&s->avg, sizeof(float), 1, file);
        fwrite(&s->size, sizeof(int), 1, file);
        
        int nameLen = strlen(s->name);
        fwrite(&nameLen, sizeof(int), 1, file);
        fwrite(s->name, sizeof(char), nameLen, file);
        
        int surnameLen = strlen(s->surname);
        fwrite(&surnameLen, sizeof(int), 1, file);
        fwrite(s->surname, sizeof(char), surnameLen, file);
        
        for (int j = 0; j < s->size; j++) {
            Course* c = &s->courses[j];
            
            int courseNameLen = strlen(c->name);
            fwrite(&courseNameLen, sizeof(int), 1, file);
            fwrite(c->name, sizeof(char), courseNameLen, file);
            
            fwrite(&c->coef, sizeof(float), 1, file);
            fwrite(&c->avg, sizeof(float), 1, file);
            
            int gradeSize = (c->grades == NULL) ? 0 : c->grades->size;
            fwrite(&gradeSize, sizeof(int), 1, file);
            
            if (gradeSize > 0) {
                fwrite(c->grades->data, sizeof(float), gradeSize, file);
            }
        }
    }
    
    fclose(file);
    printf("Promotion saved to %s\n", filename);
    return 0;
}

Prom* loadProm(char* filename) {
    if (filename == NULL) {
        fprintf(stderr, "Error: Invalid filename\n");
        return NULL;
    }
    
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return NULL;
    }
    
    int numberOfStudents;
    if (fread(&numberOfStudents, sizeof(int), 1, file) != 1) {
        fprintf(stderr, "Error: Cannot read student count\n");
        fclose(file);
        return NULL;
    }
    
    Student* students = malloc(numberOfStudents * sizeof(Student));
    if (students == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(file);
        return NULL;
    }
    
    for (int i = 0; i < numberOfStudents; i++) {
        Student* s = &students[i];
        
        fread(&s->id, sizeof(int), 1, file);
        fread(&s->age, sizeof(int), 1, file);
        fread(&s->avg, sizeof(float), 1, file);
        fread(&s->size, sizeof(int), 1, file);
        
        int nameLen;
        fread(&nameLen, sizeof(int), 1, file);
        s->name = malloc(nameLen + 1);
        if (s->name == NULL) {
            fclose(file);
            return NULL;
        }
        fread(s->name, sizeof(char), nameLen, file);
        s->name[nameLen] = '\0';
        
        int surnameLen;
        fread(&surnameLen, sizeof(int), 1, file);
        s->surname = malloc(surnameLen + 1);
        if (s->surname == NULL) {
            free(s->name);
            fclose(file);
            return NULL;
        }
        fread(s->surname, sizeof(char), surnameLen, file);
        s->surname[surnameLen] = '\0';
        
        s->courses = malloc(s->size * sizeof(Course));
        if (s->courses == NULL) {
            free(s->name);
            free(s->surname);
            fclose(file);
            return NULL;
        }
        
        for (int j = 0; j < s->size; j++) {
            Course* c = &s->courses[j];
            
            int courseNameLen;
            fread(&courseNameLen, sizeof(int), 1, file);
            c->name = malloc(courseNameLen + 1);
            if (c->name == NULL) {
                fclose(file);
                return NULL;
            }
            fread(c->name, sizeof(char), courseNameLen, file);
            c->name[courseNameLen] = '\0';
            
            fread(&c->coef, sizeof(float), 1, file);
            fread(&c->avg, sizeof(float), 1, file);
            
            int gradeSize;
            fread(&gradeSize, sizeof(int), 1, file);
            
            if (gradeSize == 0) {
                c->grades = NULL;
            } else {
                c->grades = malloc(sizeof(Grades));
                if (c->grades == NULL) {
                    fclose(file);
                    return NULL;
                }
                c->grades->size = gradeSize;
                c->grades->data = malloc(gradeSize * sizeof(float));
                if (c->grades->data == NULL) {
                    free(c->grades);
                    fclose(file);
                    return NULL;
                }
                fread(c->grades->data, sizeof(float), gradeSize, file);
            }
        }
    }
    
    fclose(file);
    
    Prom* prom = createProm(students, numberOfStudents);
    if (prom == NULL) {
        return NULL;
    }
    
    printf("Promotion loaded from %s\n", filename);
    return prom;
}
