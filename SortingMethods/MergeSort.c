//
// Created by diogoleite87 on 28/09/2022.
//

#include "Headers/employee.h"

void mergeSort(int numberOfPartition, char nameFilePartition[]) {

    int *vetSizePartition = (int *) malloc(numberOfPartition * sizeof(int));
    int *vetFinalPartition = (int *) malloc(numberOfPartition * sizeof(int));
    int *vetPositionPartition = (int *) malloc(numberOfPartition * sizeof(int));
    int *vetValueEmployeePartition = (int *) malloc(numberOfPartition * sizeof(int));
    int flagAuxFinal = 0, count, smallElement = 999999999, smallElementPosition = 0;

    FILE *file = fopen("mergeSortFileSorted.dat", "wb+");

    for (int i = 0; i <= numberOfPartition; ++i) {

        char partitionName[100];
        char str1[100];
        char str2[100] = ".dat";

        itoa(i, str1, 10);
        strcat(strcpy(partitionName, nameFilePartition), str1);
        strcat(strcpy(partitionName, partitionName), str2);

        FILE *filePartition = fopen(partitionName, "rb+");

        rewind(filePartition);

        vetSizePartition[i] = sizeFile(filePartition, 0);
        vetFinalPartition[i] = 0;
        vetPositionPartition[i] = 0;

        fseek(filePartition, vetPositionPartition[i] * sizeof(TFunc), SEEK_SET);
        TFunc *auxFunc = readRegisterEmployee(filePartition);

        vetValueEmployeePartition[i] = auxFunc->id;

        fclose(filePartition);
    }


    while (flagAuxFinal != 1) {

        count = 0;

        for (int i = 0; i < numberOfPartition; ++i) {

            if (vetFinalPartition[i] == 1) {
                count++;
            }

            if (count == numberOfPartition) {
                flagAuxFinal = 1;
            }
        }

        for (int i = 0; i < 6; ++i) {

            if (vetValueEmployeePartition[i] < smallElement && vetFinalPartition[i] != 1) {
                smallElement = vetValueEmployeePartition[i];
                smallElementPosition = i;
            }
        }

        char partitionName[100];
        char str1[100];
        char str2[100] = ".dat";

        itoa(smallElementPosition, str1, 10);
        strcat(strcpy(partitionName, nameFilePartition), str1);
        strcat(strcpy(partitionName, partitionName), str2);

        FILE *filePartition = fopen(partitionName, "rb+");

        rewind(filePartition);
        fseek(filePartition, vetPositionPartition[smallElementPosition] * sizeof(TFunc), SEEK_SET);
        TFunc *auxFunc = readRegisterEmployee(filePartition);
        saveRegisterEmployee(auxFunc, file);
        vetPositionPartition[smallElementPosition]++;

        rewind(filePartition);

        if (vetPositionPartition[smallElementPosition] == vetSizePartition[smallElementPosition]) {
            vetFinalPartition[smallElementPosition] = 1;
        } else {
            fseek(filePartition, vetPositionPartition[smallElementPosition] * sizeof(TFunc), SEEK_SET);
            TFunc *auxFunc2 = readRegisterEmployee(filePartition);
            vetValueEmployeePartition[smallElementPosition] = auxFunc2->id;
        }

        fclose(filePartition);

        smallElement = 999999999;

    }

    printPartitionEmployeeID(file, "mergeSortFileSorted.dat");

    fclose(file);
    free(vetFinalPartition);
    free(vetSizePartition);
    free(vetPositionPartition);
    free(vetValueEmployeePartition);
}
