//
// Created by diogoleite87 on 12/10/2022.
//

#include "../Headers/employee.h"

void deleteHashTable(int employerID, int partitionID) {

    char partitionName[100];
    char str1[100];
    char str2[100] = ".dat";
    int totalCompararisons;

    itoa(partitionID, str1, 10);
    strcat(strcpy(partitionName, "hashTablePartition"), str1);
    strcat(strcpy(partitionName, partitionName), str2);

    FILE *filePartition = fopen(partitionName,"ab+");

    TFunc *auxFunc = sequentialFetch(employerID, filePartition, &totalCompararisons);

    if (auxFunc != NULL) {

        fseek(filePartition, (totalCompararisons - 1) * sizeof(TFunc), SEEK_SET);

        TFunc funcHashDelet;

        funcHashDelet.id = 999999;
        sprintf(funcHashDelet.name, "%s", auxFunc->name);
        sprintf(funcHashDelet.cpf, "%s", auxFunc->cpf);
        sprintf(funcHashDelet.birthDate, "%s", auxFunc->birthDate);
        funcHashDelet.pay = auxFunc->pay;

        saveRegisterEmployee(&funcHashDelet, filePartition);

        printf("\nEmployee deleted successfully.");
    } else {
        printf("\nEmployee id not exist in the Hash Table.");
    }

    fclose(filePartition);
}