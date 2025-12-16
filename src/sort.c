#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/sort.h"
#include "../include/parser.h"


// SORT MODES

int compareBySurname(const void* a, const void* b) {
    const Student* s1 = (const Student*)a;
    const Student* s2 = (const Student*)b;
    return strcmp(s1->surname, s2->surname);
}

int compareByName(const void* a, const void* b) {
    const Student* s1 = (const Student*)a;
    const Student* s2 = (const Student*)b;
    return strcmp(s1->name, s2->name);
}

float getMinAverage(const Student* s) {
    if (s->size == 0) return 0.0;
    float min = s->courses[0].avg;
    for (int i = 1; i < s->size; i++) {
        if (s->courses[i].avg < min) {
            min = s->courses[i].avg;
        }
    }
    return min;
}

int compareByWorstGrade(const void* a, const void* b) {
    const Student* s1 = (const Student*)a;
    const Student* s2 = (const Student*)b;
    
    float min1 = getMinAverage(s1);
    float min2 = getMinAverage(s2);

    if (min2 > min1) return 1;
    if (min2 < min1) return -1;
    return 0;
}

int compareByAverage(const void* a, const void* b) {
    Student* s1 = (Student*)a;
    Student* s2 = (Student*)b;
    
    if (s2->avg > s1->avg) return 1;
    if (s2->avg < s1->avg) return -1;
    return 0;
}

//

int API_set_sorting_mode(CLASS_DATA* pClass, int mode) {
    if (pClass == NULL) return 0;
    switch(mode) {
        case ALPHA_FIRST_NAME: 
            pClass->currentCompareFunction = compareByName;
            break;
        case ALPHA_LAST_NAME: 
            pClass->currentCompareFunction = compareBySurname;
            break;
        case AVERAGE:
            pClass->currentCompareFunction = compareByAverage;
            break;
        case MINIMUM:
            pClass->currentCompareFunction = compareByWorstGrade;
            break;
        default:
            return 0;
    }
    return 1;
}

char** API_sort_students(CLASS_DATA* pClass) {
    if (pClass == NULL || pClass->prom == NULL || pClass->currentCompareFunction == NULL) {
        return NULL;
    }

    qsort(pClass->prom->students, 
          pClass->prom->number, 
          sizeof(Student), 
          pClass->currentCompareFunction);


    char** result = malloc(SIZE_TOP1 * sizeof(char*));
    if (result == NULL) return NULL;
    int limit = (pClass->prom->number < SIZE_TOP1) ? pClass->prom->number : SIZE_TOP1;

    for (int i = 0; i < SIZE_TOP1; i++) {
        if (i < limit) {
            result[i] = malloc(256 * sizeof(char)); 
            
            if (result[i] != NULL) {
                Student* s = &pClass->prom->students[i];
                sprintf(result[i], "%s %s (Moyenne: %.2f) (Note min: %.2f)", s->surname, s->name, s->avg, getMinAverage(s));
            }
        } else {
            result[i] = NULL; 
        }
    }

    return result;
}

char** getTopStudents(Prom* prom, int n) {
    if (prom == NULL || n <= 0) return NULL;

    Student* copy = malloc(prom->number * sizeof(Student));
    if (copy == NULL) return NULL;
    memcpy(copy, prom->students, prom->number * sizeof(Student));

    qsort(copy, prom->number, sizeof(Student), compareByAverage);

    char** result = malloc(n * sizeof(char*));
    if (result == NULL) {
        free(copy);
        return NULL;
    }

    int limit = (prom->number < n) ? prom->number : n;

    for (int i = 0; i < n; i++) {
        if (i < limit) {
            result[i] = malloc(256 * sizeof(char));
            if (result[i] != NULL) {
                sprintf(result[i], "%s %s (Moyenne: %.2f/20)", 
                        copy[i].surname, copy[i].name, copy[i].avg);
            }
        } else {
            result[i] = NULL;
        }
    }

    free(copy);
    return result;
}

char** getTopInCourse(Prom* prom, char* courseName, int n) {
    if (prom == NULL || courseName == NULL || n <= 0) return NULL;

    typedef struct {
        Student* student;
        float courseAvg;
    } StudentCourseAvg;

    StudentCourseAvg* temp = malloc(prom->number * sizeof(StudentCourseAvg));
    if (temp == NULL) return NULL;

    int count = 0;
    for (int i = 0; i < prom->number; i++) {
        Course* course = findCourseByName(&prom->students[i], courseName);
        if (course != NULL && course->grades != NULL && course->grades->size > 0) {
            temp[count].student = &prom->students[i];
            temp[count].courseAvg = course->avg;
            count++;
        }
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (temp[j].courseAvg > temp[i].courseAvg) {
                StudentCourseAvg swap = temp[i];
                temp[i] = temp[j];
                temp[j] = swap;
            }
        }
    }

    char** result = malloc(n * sizeof(char*));
    if (result == NULL) {
        free(temp);
        return NULL;
    }

    int limit = (count < n) ? count : n;

    for (int i = 0; i < n; i++) {
        if (i < limit) {
            result[i] = malloc(256 * sizeof(char));
            if (result[i] != NULL) {
                Student* s = temp[i].student;
                sprintf(result[i], "%s %s (%s: %.2f/20)", 
                        s->surname, s->name, courseName, temp[i].courseAvg);
            }
        } else {
            result[i] = NULL;
        }
    }

    free(temp);
    return result;
}



// J'utilise pas mais peut etre utilise en changeant plus tard
Student* getTop10Students(Prom* prom, int* resultSize) {
    if (prom == NULL || resultSize == NULL) {
        fprintf(stderr, "Error: Invalid parameters for getTop10Students\n");
        return NULL;
    }
    
    int size = (prom->number < 10) ? prom->number : 10;
    *resultSize = size;
    
    Student* copy = malloc(prom->number * sizeof(Student));
    if (copy == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL;
    }
    
    memcpy(copy, prom->students, prom->number * sizeof(Student));
    
    qsort(copy, prom->number, sizeof(Student), compareByAverage);
    
    Student* top10 = malloc(size * sizeof(Student));
    if (top10 == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        free(copy);
        return NULL;
    }
    
    memcpy(top10, copy, size * sizeof(Student));
    
    free(copy);
    return top10;
}

Student* getTop3InCourse(Prom* prom, char* courseName) {
    if (prom == NULL || courseName == NULL) {
        fprintf(stderr, "Error: Invalid parameters for getTop3InCourse\n");
        return NULL;
    }
    
    typedef struct {
        Student* student;
        float courseAvg;
    } StudentCourseAvg;
    
    StudentCourseAvg* temp = malloc(prom->number * sizeof(StudentCourseAvg));
    if (temp == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL;
    }
    
    int count = 0;
    
    for (int i = 0; i < prom->number; i++) {
        Course* course = findCourseByName(&prom->students[i], courseName);
        if (course != NULL && course->grades != NULL && course->grades->size > 0) {
            temp[count].student = &prom->students[i];
            temp[count].courseAvg = course->avg;
            count++;
        }
    }
    
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (temp[j].courseAvg > temp[i].courseAvg) {
                StudentCourseAvg tmp = temp[i];
                temp[i] = temp[j];
                temp[j] = tmp;
            }
        }
    }
    
    Student* top3 = malloc(3 * sizeof(Student));
    if (top3 == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        free(temp);
        return NULL;
    }
    
    int size = (count < 3) ? count : 3;
    
    for (int i = 0; i < size; i++) {
        top3[i] = *(temp[i].student);
    }
    
    for (int i = size; i < 3; i++) {
        top3[i].id = -1;
    }
    
    free(temp);
    return top3;
}
