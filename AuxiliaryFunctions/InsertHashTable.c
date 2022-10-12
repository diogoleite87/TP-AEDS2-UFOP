//
// Created by diogoleite87 on 12/10/2022.
//

#include "../Headers/employee.h"

void insertHashTable(TFunc *funcHashTableInsert,int employerID, int partitionID) {

    char partitionName[100];
    char str1[100];
    char str2[100] = ".dat";
    int totalCompararisons;

    itoa(partitionID, str1, 10);
    strcat(strcpy(partitionName, "hashTablePartition"), str1);
    strcat(strcpy(partitionName, partitionName), str2);


    FILE *filePartition = fopen(partitionName,"ab+");

    TFunc *auxFunc = sequentialFetch(funcHashTableInsert->id, filePartition, &totalCompararisons);

    if (auxFunc == NULL) {
        saveRegisterEmployee(funcHashTableInsert, filePartition);
        printf("\nEmployee entered successfully.");
    } else {
        printf("\nEmployee id already exist in the Hash Table.");
    }

    fclose(filePartition);
}