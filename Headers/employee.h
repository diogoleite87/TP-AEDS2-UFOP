#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct File{
    TFunc *func;
    long init_p;
    long end_p;
    FILE *filePartition;
}TVetFile;

void saveRegisterEmployee(TFunc *func, FILE *out);
TFunc *readRegisterEmployee(FILE *in);
void createDataBase(FILE *arq, int nFunc, int *vet);
TFunc *binaryFetch(int id, FILE *file, int sizeFile, int *totalComparisons);
void printEmployee (TFunc *func);
TFunc *sequentialFetch(int id, FILE *file, int *totalComparisons);
void shuffleVet(int *vet, int vetSize);
TFunc *insertionSort(FILE *file, int sizeFile);
void keySort(FILE *file, FILE *sortedFile, int sizeFile);
int sizeFile(FILE *file, int contSizeFile);
void printPartitionEmployeeID(FILE *file, char partitionName[]);
int allVetFrozen (int vet[6]);
void mergeSort(int numberOfPartition, char nameFilePartition[]);
int substitutionSelection (FILE *file, char nameFilePartition[]);
int naturalSelection(FILE *file, char nameFilePartition[]);
void printAllEmployeeFile(FILE *file);
void binaryTreeOfWinners(int numberOfPartition, char nameFilePartition[]);
void treeWinner(TFunc **func, FILE *file, int sizeInTreeOfWinners, int *auxTreeWinner);
void makePartitionHashTable (int numberOfPartition);
void hashTable(FILE *file, int numberOfPartition, int sizeFile);
TFunc *searchHashTable(int employerID, int partitionID);
void insertHashTable(TFunc *funcHashTableInsert,int employerID, int partitionID);
void deleteHashTable(int employerID, int partitionID);

#endif