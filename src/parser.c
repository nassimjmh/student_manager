#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parser.h"
#include "../include/structures.h"

Student parseStudentLine(char* line) {
    char copy[512];
    strcpy(copy, line);
    
    Student student;
    student.courses = NULL;
    student.size = 0;
    student.avg = 0.0;
    student.name = NULL;
    student.surname = NULL;

    char* token = strtok(copy, ";");
    if (token == NULL) return student;
    student.id = atoi(token);

    token = strtok(NULL, ";");
    if (token == NULL) return student;
    student.name = malloc(strlen(token) + 1);
    if (student.name != NULL) {
        strcpy(student.name, token);
    }

    token = strtok(NULL, ";");
    if (token == NULL) return student;
    student.surname = malloc(strlen(token) + 1);
    if (student.surname != NULL) {
        strcpy(student.surname, token);
    }

    token = strtok(NULL, ";");
    if (token == NULL) return student;
    student.age = atoi(token);

    return student;
}

Course parseCourseLine(char* line) {
    char copy[512];
    strcpy(copy, line);
    
    Course course;
    course.grades = NULL;
    course.avg = 0.0;
    course.name = NULL;
    
    char* token = strtok(copy, ";");
    if (token == NULL) return course;
    course.name = malloc(strlen(token) + 1);
    if (course.name != NULL) {
        strcpy(course.name, token);
    }
    
    token = strtok(NULL, ";");
    if (token == NULL) return course;
    course.coef = atof(token);
    
    return course;
}

void updateCourseAverage(Course* course) {
    if (course == NULL || course->grades == NULL || course->grades->size == 0) {
        if (course != NULL) {
            course->avg = 0.0;
        }
        return;
    }
    
    float sum = 0.0;
    for (int i = 0; i < course->grades->size; i++) {
        sum += course->grades->data[i];
    }
    course->avg = sum / course->grades->size;
}

Student* findStudentById(Prom* prom, int id) {
    if (prom == NULL) return NULL;
    
    for (int i = 0; i < prom->number; i++) {
        if (prom->students[i].id == id) {
            return &prom->students[i];
        }
    }
    return NULL;
}

Student* findStudentByName(Prom* prom, char* firstname, char* lastname) {
    if (prom == NULL || firstname == NULL || lastname == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < prom->number; i++) {
        if (strcmp(prom->students[i].name, firstname) == 0 && 
            strcmp(prom->students[i].surname, lastname) == 0) {
            return &prom->students[i];
        }
    }
    return NULL;
}

Course* findCourseByName(Student* student, char* courseName) {
    if (student == NULL || courseName == NULL) return NULL;
    
    for (int i = 0; i < student->size; i++) {
        if (strcmp(student->courses[i].name, courseName) == 0) {
            return &student->courses[i];
        }
    }
    return NULL;
}

void updateStudentAverage(Student* student) {
    if (student == NULL) return;
    
    float sum = 0.0;
    float totalCoef = 0.0;
    
    for (int i = 0; i < student->size; i++) {
        if (student->courses[i].grades != NULL && 
            student->courses[i].grades->size > 0) {
            sum += student->courses[i].avg * student->courses[i].coef;
            totalCoef += student->courses[i].coef;
        }
    }
    
    student->avg = (totalCoef > 0) ? sum / totalCoef : 0.0;
}

void parseAndAddGrade(char* line, Prom* prom) {
    if (line == NULL || prom == NULL) return;
    
    char copy[512];
    strcpy(copy, line);
    
    char* token = strtok(copy, ";");
    if (token == NULL) return;
    int studentId = atoi(token);
    
    token = strtok(NULL, ";");
    if (token == NULL) return;
    char courseName[256];
    strcpy(courseName, token);
    
    token = strtok(NULL, ";");
    if (token == NULL) return;
    float grade = atof(token);
    
    Student* student = findStudentById(prom, studentId);
    if (student == NULL) return;
    
    Course* course = findCourseByName(student, courseName);
    if (course == NULL) return;
    
    if (course->grades == NULL) {
        float* data = malloc(sizeof(float));
        if (data == NULL) return;
        data[0] = grade;
        course->grades = createGrades(data, 1);
        free(data);
    } else {
        float* newData = realloc(course->grades->data, 
                                (course->grades->size + 1) * sizeof(float));
        if (newData == NULL) return;
        
        course->grades->data = newData;
        course->grades->data[course->grades->size] = grade;
        course->grades->size++;
    }
    
    updateCourseAverage(course);
    updateStudentAverage(student);
}

Prom* loadFile(char* filename) {
    if (filename == NULL) {
        fprintf(stderr, "Error: Invalid filename\n");
        return NULL;
    }
    
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return NULL;
    }
    
    char line[512];
    Student* tempStudents = NULL;
    Course* tempCourses = NULL;
    int studentCount = 0;
    int courseCount = 0;
    
    typedef enum { NONE, STUDENTS, COURSES, GRADES } Section;
    Section currentSection = NONE;
    
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\r\n")] = 0;
        
        if (strlen(line) == 0) continue;
        
        if (strcmp(line, "ETUDIANTS") == 0) {
            currentSection = STUDENTS;
            fgets(line, sizeof(line), file);
            continue;
        } else if (strcmp(line, "MATIERES") == 0) {
            currentSection = COURSES;
            fgets(line, sizeof(line), file);
            continue;
        } else if (strcmp(line, "NOTES") == 0) {
            currentSection = GRADES;
            fgets(line, sizeof(line), file);
            continue;
        }
        
        if (currentSection == STUDENTS) {
            tempStudents = realloc(tempStudents, 
                                  (studentCount + 1) * sizeof(Student));
            if (tempStudents == NULL) {
                fclose(file);
                return NULL;
            }
            tempStudents[studentCount] = parseStudentLine(line);
            studentCount++;
        } else if (currentSection == COURSES) {
            tempCourses = realloc(tempCourses, 
                                 (courseCount + 1) * sizeof(Course));
            if (tempCourses == NULL) {
                fclose(file);
                free(tempStudents);
                return NULL;
            }
            tempCourses[courseCount] = parseCourseLine(line);
            courseCount++;
        }
    }
    
    for (int i = 0; i < studentCount; i++) {
        tempStudents[i].courses = malloc(courseCount * sizeof(Course));
        if (tempStudents[i].courses == NULL) {
            fclose(file);
            free(tempStudents);
            free(tempCourses);
            return NULL;
        }
        
        for (int j = 0; j < courseCount; j++) {
            tempStudents[i].courses[j].name = malloc(strlen(tempCourses[j].name) + 1);
            if (tempStudents[i].courses[j].name != NULL) {
                strcpy(tempStudents[i].courses[j].name, tempCourses[j].name);
            }
            tempStudents[i].courses[j].coef = tempCourses[j].coef;
            tempStudents[i].courses[j].avg = 0.0;
            tempStudents[i].courses[j].grades = NULL;
        }
        tempStudents[i].size = courseCount;
    }
    
    for (int i = 0; i < courseCount; i++) {
        if (tempCourses[i].name != NULL) {
            free(tempCourses[i].name);
        }
    }
    free(tempCourses);
    
    if (studentCount == 0 || tempStudents == NULL) {
        fprintf(stderr, "Error: No students loaded from file\n");
        fclose(file);
        return NULL;
    }
    
    Prom* prom = createProm(tempStudents, studentCount);
    if (prom == NULL) {
        fclose(file);
        return NULL;
    }
    
    fseek(file, 0, SEEK_SET);
    currentSection = NONE;
    
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\r\n")] = 0;
        
        if (strcmp(line, "NOTES") == 0) {
            currentSection = GRADES;
            fgets(line, sizeof(line), file);
            continue;
        }
        
        if (currentSection == GRADES && strlen(line) > 0) {
            parseAndAddGrade(line, prom);
        }
    }
    
    fclose(file);
    for (int i = 0; i < prom->number; i++) {
        updateStudentValidation(&prom->students[i]);
    }
    printf("File loaded: %d students, %d courses\n", studentCount, courseCount);
    return prom;
}
