//
// Created by diogoleite87 on 28/09/2022.
//

#include "Headers/employee.h"

void printPartitionEmployeeID(FILE *file, char partitionName[]) {

    printf("\nIDs employee of partition %s: \n --->  ", partitionName);

    for (int i = 0; i < sizeFile(file, 0); ++i) {

        fseek(file, i * sizeof(TFunc), SEEK_SET) ;
        TFunc *aux = readRegisterEmployee(file);

        printf(" %i ", aux->id);
    }

    printf("\n");
}