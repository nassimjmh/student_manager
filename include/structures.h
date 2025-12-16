#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct grades {
    float* data;    /**< Dynamic array of grade values */
    int size;       /**< Number of grades stored */
} Grades;

typedef struct course {
    float coef;             /**< Course coefficient for weighted average */
    float avg;              /**< Average grade for this course */
    char* name;             /**< Course name (dynamically allocated) */
    struct grades* grades;  /**< Pointer to grades structure */
} Course;

typedef struct student {
    int age;                /**< Student age */
    int id;                 /**< Unique student identifier */
    int size;               /**< Number of courses taken */
    float avg;              /**< Overall weighted average */
    char* name;             /**< First name (dynamically allocated) */
    char* surname;          /**< Last name (dynamically allocated) */
    struct course* courses; /**< Array of courses */
    unsigned long long validation_flags; 
} Student;

typedef struct prom {
    Student* students;  /**< Array of students */
    int number;         /**< Number of students in the cohort */
} Prom;

typedef enum {
    ALPHA_FIRST_NAME, // Tri par nom de famille
    ALPHA_LAST_NAME,  // Tri par prénom
    AVERAGE,          // Tri par moyenne générale
    MINIMUM           // Tri par la note minimale
} SortingMode;

typedef int (*CompareFn)(const void*, const void*); 

typedef struct class_data {
    CompareFn currentCompareFunction; /**< Current comparison function for sorting */
    Prom* prom;                      /**< Pointer to the Prom structure */
} CLASS_DATA;

typedef enum {
    MATHEMATIQUES = 0,
    PHYSIQUE,
    INFORMATIQUE,
    CHIMIE,
    BIOLOGIE,
    HISTOIRE,
    GEOGRAPHIE,
    FRANCAIS,
    ANGLAIS,
    EPS,
    PHILOSOPHIE,
    ECONOMIE,
    SOCIOLOGIE,
    ARTS_PLASTIQUES,
    MUSIQUE,
    TECHNOLOGIE,
    LATIN,
    ESPAGNOL,
    ALLEMAND,
    SCIENCES_SOCIALES
} CourseIndex;

#define SCIENCES_MASK ( \
    (1ULL << MATHEMATIQUES) | \
    (1ULL << PHYSIQUE) | \
    (1ULL << INFORMATIQUE) | \
    (1ULL << CHIMIE) | \
    (1ULL << BIOLOGIE) | \
    (1ULL << TECHNOLOGIE) \
)

#define HUMANITIES_MASK ( \
    (1ULL << HISTOIRE) | \
    (1ULL << GEOGRAPHIE) | \
    (1ULL << FRANCAIS) | \
    (1ULL << ANGLAIS) | \
    (1ULL << EPS) | \
    (1ULL << PHILOSOPHIE) | \
    (1ULL << ECONOMIE) | \
    (1ULL << SOCIOLOGIE) | \
    (1ULL << ARTS_PLASTIQUES) | \
    (1ULL << MUSIQUE) | \
    (1ULL << LATIN) | \
    (1ULL << ESPAGNOL) | \
    (1ULL << ALLEMAND) | \
    (1ULL << SCIENCES_SOCIALES) \
)

// Le masque complet pour l'année (toutes les matières + EPS)
#define YEAR_MASK (SCIENCES_MASK | HUMANITIES_MASK)

void updateStudentValidation(Student* s);

Grades* createGrades(float* data, int size);

Course* createCourse(float coef, float avg, char* name, Grades* grades);

Student* createStudent(int age, int id, int size, float avg, char* name, char* surname, Course* courses);

Prom* createProm(Student* students, int number);

void destroyGrades(Grades* grades);

void destroyCourse(Course* course);

void destroyStudentContent(Student* student);

void destroyProm(Prom* prom);

#endif /* STRUCTURES_H */
