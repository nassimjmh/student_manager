#include <stdio.h>
#include <stdlib.h>
#include "../include/structures.h"
#include "../include/parser.h"
#include "../include/save_load.h"
#include "../include/display.h"
#include "../include/sort.h"
#include "../include/operations.h"

// Sécurité au cas où SIZE_TOP1 n'est pas dans sort.h
#ifndef SIZE_TOP1
#define SIZE_TOP1 10
#endif

void printAndFreeResults(char** results) {
    if (results == NULL) {
        printf("Aucun résultat retourné.\n");
        return;
    }
    for (int i = 0; i < SIZE_TOP1; i++) {
        if (results[i] != NULL) {
            printf("[%d] %s\n", i + 1, results[i]);
            free(results[i]);
        }
    }
    free(results);
}

int main(int argc, char* argv[]) {
    char* dataFile = "data.txt";
    if (argc > 1) {
        dataFile = argv[1];
    }

    Prom* prom = loadFile(dataFile);
    if (prom == NULL) {
        fprintf(stderr, "Error: Failed to load data file\n");
        return -1;
    }
    
    // Test Sauvegarde Binaire
    printf("\nTesting Binary Save/Load\n");
    if (saveProm(prom, "bin/prom.bin") == 0) {
        Prom* prom2 = loadProm("bin/prom.bin");
        if (prom2 != NULL) {
            printf("Binary save/load test successful!\n");
            destroyProm(prom2);
        }
    }

    // Initialisation de la structure CLASS_DATA
    CLASS_DATA* classData = malloc(sizeof(CLASS_DATA));
    if (classData == NULL) {
        destroyProm(prom);
        return -1;
    }
    classData->prom = prom;
    classData->currentCompareFunction = NULL; 
    if (classData->prom == NULL) {
        free(classData);
        destroyProm(prom);
        return -1;
    }
    /*
    printf("\nTOP %d - GENERAL\n", SIZE_TOP1);
    char** topGeneral = getTopStudents(classData->prom, SIZE_TOP1);
    printAndFreeResults(topGeneral);

    printf("\nTOP %d - MATHÉMATIQUES\n", SIZE_TOP1);
    char** topMaths = getTopInCourse(classData->prom, "Mathematiques", SIZE_TOP1);
    printAndFreeResults(topMaths); 


        
    printf("\nTest 1 : Tri Alphabetique (Prenom) ===\n");
    API_set_sorting_mode(classData, ALPHA_FIRST_NAME); 
    char** namesList = API_sort_students(classData);
    printAndFreeResults(namesList);

    printf("\nTest 2 : Tri Alphabetique (Nom) ===\n");
    API_set_sorting_mode(classData, ALPHA_LAST_NAME);
    char** surnamesList = API_sort_students(classData);
    printAndFreeResults(surnamesList);

    printf("\nTest 3 : Tri par Moyenne\n");
    API_set_sorting_mode(classData, AVERAGE);
    char** avgList = API_sort_students(classData);
    printAndFreeResults(avgList);

    printf("\nTest 4 : Tri par Note Minimale\n"); 
    API_set_sorting_mode(classData, MINIMUM);
    char** minList = API_sort_students(classData);
    printAndFreeResults(minList);

    API_set_sorting_mode(classData, ALPHA_LAST_NAME); // Juste pour avoir dans l'ordre alphabétique
    char** tempList = API_sort_students(classData);
    if (tempList != NULL) {
        for (int i = 0; i < SIZE_TOP1; i++) {
            free(tempList[i]); 
        }
        free(tempList); 
    }
    for (int i = 0; i < classData->prom->number; i++) {
             updateStudentValidation(&classData->prom->students[i]);
        }
    API_display_results_per_field(classData);


    // --- Nettoyage Final ---
    printf("\n=== Cleanup ===\n");
    
    if (classData != NULL) {
        free(classData);
    }
    */

    // TEST NORMALISATION NOTES

    Recalcul_data* recalculData = malloc(sizeof(Recalcul_data));
    if (recalculData == NULL) {
        return -1;
    }
    recalculData->func = normalisation;

    printf("\nAvant : Tri par Moyenne\n");
    API_set_sorting_mode(classData, AVERAGE);
    char** avgList = API_sort_students(classData);
    printAndFreeResults(avgList);

    miseAJourNotes(classData->prom, recalculData);

    printf("\nAprès : Tri par Moyenne\n");
    char** avgList2 = API_sort_students(classData);
    printAndFreeResults(avgList2);


    destroyProm(prom);
    
    printf("All memory freed successfully.\n");
    printf("\nProgram completed successfully!\n");
    
    return 0;
}