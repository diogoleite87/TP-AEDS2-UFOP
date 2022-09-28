//
// Created by diogoleite87 on 28/09/2022.
//

#include "Headers/employee.h"

void mergeSort(int numberOfPartition, char nameFilePartition[]) {

    printf("\nPerforming MergeSort...");

    int *vetAux = (int *) malloc(numberOfPartition * sizeof(int));
    int *vetAux2 = (int *) malloc(numberOfPartition * sizeof(int));
    int *vetFlagAux = (int *) malloc(numberOfPartition * sizeof(int));
    int flagAux = numberOfPartition;

    FILE *file = fopen("mergeSortFileSorted.dat", "wb+");

    for (int i = 0; i <= numberOfPartition; ++i) {

        char partitionName[100];
        char str1[100] = "substitutionSelectionPartition";
        char str2[100];
        char str3[100] = ".dat";

        itoa(i,str2,10);
        strcat(strcpy(partitionName, nameFilePartition), str2);
        strcat(strcpy(partitionName, partitionName), str3);

        FILE *filePartition = fopen(partitionName, "rb+");

        rewind(filePartition);

        vetAux[i] = sizeFile(filePartition, 0);
        vetAux2[i] = 0;

        fclose(filePartition);
    }

    while (flagAux >= 0) {

        FILE *fileAux = fopen("fileAuxMergeSort.dat", "wb+");

        flagAux = numberOfPartition;

        for (int i = 0; i <= numberOfPartition; ++i) {

            char partitionName[100];
            char str1[100] = "substitutionSelectionPartition";
            char str2[100];
            char str3[100] = ".dat";

            itoa(i,str2,10);
            strcat(strcpy(partitionName, nameFilePartition), str2);
            strcat(strcpy(partitionName, partitionName), str3);

            FILE *filePartition = fopen(partitionName, "rb+");

            if (vetAux[i] != 0) {

                fseek(filePartition,  vetAux2[i] * sizeof(TFunc), SEEK_SET) ;
                TFunc *func = readRegisterEmployee(filePartition);
                vetAux2[i]++;

                saveRegisterEmployee(func, fileAux);
                vetAux[i]--;
            }

            for (int j = 0; j <= numberOfPartition; ++j) {

                if (vetAux[j] == 0) {
                    vetFlagAux[j] = 1;
                } else {
                    vetFlagAux[j] = 0;
                }

            }

            fclose(filePartition);
        }

        for (int k = 0; k <= numberOfPartition; ++k) {

            if (vetAux[k] == 0) {
                flagAux--;
            }

        }


        rewind(fileAux);
        int sizeFileAux = sizeFile(fileAux, 0);


        insertionSort(fileAux, sizeFileAux);


        rewind(fileAux);

        for (int i = 0; i < sizeFileAux; ++i) {

            TFunc *auxFunc = readRegisterEmployee(fileAux);
            saveRegisterEmployee(auxFunc, file);

        }


        fclose(fileAux);

    }

    printPartitionEmployeeID(file, "mergeSortFileSorted.dat");

    fclose(file);
    free(vetAux2);
    free(vetFlagAux);
    free(vetAux);

}
