#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <stdlib.h>

typedef struct Employee {
    int id;
    char name[50];
    char cpf[15];
    char birthDate[11];
    double pay;
} TFunc;

struct KeyID {
    int id;
    long RRN;
};

void saveRegisterEmployee(TFunc *func, FILE *out);
TFunc *readRegisterEmployee(FILE *in);
void createDataBase(FILE *arq, int nFunc, int *vet);
TFunc *binaryFetch(int id, FILE *file, int sizeFile, int *totalComparisons);
void printEmployee (TFunc *func);
TFunc *sequentialFetch(int id, FILE *file, int *totalComparisons);
void shuffleVet(int *vet, int vetSize);
TFunc *insertionSort(FILE *file, int sizeFile);
TFunc *keySort(FILE *file, FILE *sortedFile, int sizeFile);
int sizeFile(FILE *file, int contSizeFile);
TFunc *printPartitionEmployeeID(FILE *file, char partitionName[]);
int allVetFrozen (int vet[6]);
TFunc *substitutionSelection (FILE *file);

#endif