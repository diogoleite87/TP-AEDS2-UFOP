//
// Created by diogoleite87 on 11/10/2022.
//

#include "../Headers/employee.h"
void makePartitionHashTable (int numberOfPartition) {

    for (int i = 0; i < numberOfPartition; ++i) {

        char partitionName[100];
        char str1[100];
        char str2[100] = ".dat";

        itoa(i, str1, 10);
        strcat(strcpy(partitionName, "hashTablePartition"), str1);
        strcat(strcpy(partitionName, partitionName), str2);

        FILE *file = fopen(partitionName,"wb+");

        fclose(file);
    }

}
