#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "employee.h"

void saveRegisterEmployee(TFunc *func, FILE *out) {
    fwrite(&func->id, sizeof(int), 1, out);
    fwrite(func->name, sizeof(char), sizeof(func->name), out);
    fwrite(func->cpf, sizeof(char), sizeof(func->cpf), out);
    fwrite(func->birthDate, sizeof(char), sizeof(func->birthDate), out);
    fwrite(&func->pay, sizeof(double), 1, out);
}

TFunc *readRegisterEmployee(FILE *in) {
    TFunc *func = (TFunc*) malloc (sizeof(TFunc));

    if ( 0 >= fread(&func->id, sizeof(int), 1, in)) {
        free(func);
        return NULL;
    }

    fread(func->name, sizeof(char), sizeof(func->name), in);
    fread(func->cpf, sizeof(char), sizeof(func->cpf), in);
    fread(func->birthDate, sizeof(char), sizeof(func->birthDate), in);
    fread(&func->pay, sizeof(double), 1, in);

    return func;
}

void shuffleVet(int *vet, int vetSize)
{

    for (int i = 0; i < vetSize; i++) {
        vet[i] = i + 1;
    }

    for (int i = 0; i < vetSize; i++)
    {
        int r = rand() % vetSize;

        int temp = vet[i];
        vet[i] = vet[r];
        vet[r] = temp;
    }

}

void createDataBase(FILE *arq, int nFunc, int *vet) {
    for(int i = 1; i <= nFunc; i++) {

        printf("Creating random employee %i..\n", i);
        TFunc func;

        func.id = vet[i - 1];

        char auxName[15];
        for(int j = 0; j < 15; j++) {
            auxName[j]= 'a' + (char)(rand()%26);
        }

        sprintf(func.name, "%s", auxName);
        sprintf(func.cpf, "111.111.111-11");
        sprintf(func.birthDate, "01/08/2021");
        func.pay = 1000 + rand() % 10000;
        fseek(arq, (i-1)* sizeof(TFunc), SEEK_SET);
        saveRegisterEmployee(&func, arq);
    }
}

TFunc *binaryFetch(int id, FILE *file, int sizeFile, int *totalComparisons) {

    int left = 0, right = sizeFile - 1;

    rewind(file);

    while (left <= right) {
        int middle = (left+right) / 2;
        fseek(file, middle * sizeof(TFunc), SEEK_SET);
        TFunc *func = readRegisterEmployee(file);

        if (id == func -> id) {
            *totalComparisons += 1;
            return func;
        } else if (func->id < id) {
            *totalComparisons += 1;
            left = middle+1;
        } else {
            *totalComparisons += 1;
            right = middle-1;
        }
    }

    return NULL;
}

void printEmployee (TFunc *func) {
    printf("\nRegister found: \n");
    printf("ID: %d\n", func->id);
    printf("Name: %s\n", func->name);
    printf("CPF: %s\n", func->cpf);
    printf("Birth of Date: %s\n", func->birthDate);
    printf("Payment: %.2f\n", func->pay);
}

TFunc *sequentialFetch(int id, FILE *file, int *totalComparisons) {
    int position = 0;

    while (!feof(file)) {

        fseek(file, position * sizeof(TFunc), SEEK_SET) ;
        TFunc *func = readRegisterEmployee(file);

        position++;

        if (func == NULL) {
            *totalComparisons += 1;
            return NULL;
        } else if (id == func->id) {
            *totalComparisons += 1;
            return func;
        } else {
            *totalComparisons += 1;
        }

    }

    return NULL;
}

TFunc *insertionSort(FILE *file, int sizeFile) {

    printf("\nSorting with Insertion Sort...");
    rewind(file);
    int i;

    for (int j = 2; j <= sizeFile; j++) {

        fseek(file, (j - 1) * sizeof(TFunc), SEEK_SET);
        TFunc *auxJ = readRegisterEmployee(file);

        i = j - 1;
        fseek(file, (i - 1) * sizeof(TFunc), SEEK_SET);
        do{
            TFunc *auxI = readRegisterEmployee(file);
            if( (auxI->id < auxJ->id)){
                break;
            }

            fseek(file, i * sizeof(TFunc), SEEK_SET);

            saveRegisterEmployee(auxI, file);
            i = i - 1;
            fseek(file, (i - 1) * sizeof(TFunc), SEEK_SET);

            free(auxI);

        }while ((i > 0) );

        fseek(file, (i) * sizeof(TFunc), SEEK_SET);
        saveRegisterEmployee(auxJ, file);
        free(auxJ);
    }

    fflush(file);
}

TFunc *keySort(FILE *file) {
    printf("\nSorting for KeySort...");

    int position = 0;

    while (!feof(file)) {

        fseek(file, position * sizeof(TFunc), SEEK_SET);
        TFunc *func = readRegisterEmployee(file);

        position++;
    }
    
}

int main() {
    printf("Starting...\n");

    int pick;

    printf("\nEnter an option: \n 1 - Create random .dat file; \n 2 - Read existing .dat file.\n   ---> ");
    scanf("%i", &pick);

    if (pick == 1) {
        FILE *file = fopen("register.dat", "wb+");

        if (file != NULL) {

            int numFunc = 0, idEmployee = 0, sortingMethod = 0;
            int *vet, totalComparisonsSequential = 0, totalComparisonsBinaryFetch = 0;
            double timeSpentDefault = 0.0, timeSpentBinaryFetch = 0.0;

            printf("Input the total number of employees: ");
            scanf("%i", &numFunc);

            printf("Input the id of Employee you want to find: ");
            scanf("%i", &idEmployee);

            vet = (int *)malloc(numFunc * sizeof(int));

            shuffleVet(vet, numFunc);

            createDataBase(file, numFunc, vet);

            clock_t begin = clock();

            TFunc *func = sequentialFetch(idEmployee, file, &totalComparisonsSequential);

            clock_t end = clock();
            timeSpentDefault += (double)(end - begin) / CLOCKS_PER_SEC;

            if (func == NULL) {
                printf("\nRegister not found.\n");
            } else {
                printf("\nRecord found in sequential: \n");
                printEmployee(func);
            }

            printf("\nInput Sorting method: \n 1 - InsertionSort;\n 2 - KeySort. \n   ---> ");
            scanf("%i", &sortingMethod);

            if (sortingMethod == 1) {
                insertionSort(file, numFunc);
            } else {
                keySort(file);
            }

            /* int position = 0;

            while (!feof(file)) {

                fseek(file, position * sizeof(TFunc), SEEK_SET);
                position++;
                TFunc *aux = readRegisterEmployee(file);
                printEmployee(aux);
            } */

            printf("\nPerforming binary search...");

            clock_t beginBinary = clock();

            TFunc *funcBinaryFetch = binaryFetch(idEmployee, file, numFunc, &totalComparisonsBinaryFetch);

            clock_t endBinary = clock();
            timeSpentBinaryFetch += (double)(endBinary - beginBinary) / CLOCKS_PER_SEC;

            if (funcBinaryFetch == NULL) {
                printf("\nRegister not found.\n");
            } else {
                printf("\nRecord found in Binary Fetch: \n");
                printEmployee(funcBinaryFetch);
            }

            printf("\nThe elapsed time in sequential fetch is %f seconds.\n", timeSpentDefault);
            printf("Total of comparisons in sequential fetch: %i.\n", totalComparisonsSequential);

            printf("\nThe elapsed time in Binary Fetch is %f seconds.\n", timeSpentBinaryFetch);
            printf("Total of comparisons in Binary Fetch: %i.\n", totalComparisonsBinaryFetch);

            free(func);
            free(vet);
            fclose(file);

        } else {
            printf("Err file.\n");
            return 1;
        }
    } else {

        char nameFile[50];

        printf("\nEnter the file name: ");
        scanf("%s", &nameFile);

        FILE *file = fopen(nameFile, "rb+");

        if (file != NULL) {

            int idEmployee, totalComparisonsSequential = 0, sortingMethod = 0, totalComparisonsBinaryFetch = 0;
            double timeSpentDefault = 0.0, timeSpentBinaryFetch = 0.0;;

            printf("\nOk!\n");

            printf("Input the id of Employee you want to find: ");
            scanf("%i", &idEmployee);

            clock_t begin = clock();

            TFunc *func = sequentialFetch(idEmployee, file, &totalComparisonsSequential);

            clock_t end = clock();
            timeSpentDefault += (double)(end - begin) / CLOCKS_PER_SEC;

            if (func == NULL) {
                printf("\nRegister not found.\n");
            } else {
                printf("\nRecord found in sequential: \n");
                printEmployee(func);
            }

            printf("\nInput Sorting method: \n 1 - InsertionSort;\n 2 - KeySort. \n   ---> ");
            scanf("%i", &sortingMethod);

            if (sortingMethod == 1) {
                insertionSort(file, 100);
            } else {
                keySort(file);
            }

            /* int position = 0;

            while (!feof(file)) {

                fseek(file, position * sizeof(TFunc), SEEK_SET);
                position++;
                TFunc *aux = readRegisterEmployee(file);
                printEmployee(aux);
            } */

            printf("\nPerforming binary search...");

            clock_t beginBinary = clock();

            TFunc *funcBinaryFetch = binaryFetch(idEmployee, file, sizeof(file), &totalComparisonsBinaryFetch);

            clock_t endBinary = clock();
            timeSpentBinaryFetch += (double)(endBinary - beginBinary) / CLOCKS_PER_SEC;

            if (funcBinaryFetch == NULL) {
                printf("\nRegister not found.\n");
            } else {
                printf("\nRecord found in Binary Fetch: \n");
                printEmployee(funcBinaryFetch);
            }

            printf("\nThe elapsed time in Sequential Fetch is %f seconds.\n", timeSpentDefault);
            printf("Total of comparisons in Sequential Fetch: %i.\n", totalComparisonsSequential);

            printf("\nThe elapsed time in Binary Fetch is %f seconds.\n", timeSpentBinaryFetch);
            printf("Total of comparisons in Binary Fetch: %i.\n", totalComparisonsBinaryFetch);

            free(func);
            fclose(file);

        } else {
            printf("Err file.\n");
            return 1;
        }
    }

    return 0;
}
