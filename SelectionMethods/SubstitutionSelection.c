//
// Created by diogoleite87 on 28/09/2022.
//

#include "Headers/employee.h"

void substitutionSelection (FILE *file) {

    int numberOfPartition = 0, contSizeFile = 0, position = 6, smallElementPosition = 0, smallElement = 999999, sizeFileAux = 0, selectedPosition = 0;
    struct Employee func[6];
    int auxVetFunc [6] = {0, 0, 0, 0, 0, 0};

    rewind(file);

    sizeFileAux = sizeFile(file, contSizeFile);


    printf("\nPerforming substitution selection...");

    for (int i = 0; i < 6; ++i) {
        fseek(file, i * sizeof(TFunc), SEEK_SET);

        TFunc *aux = readRegisterEmployee(file);
        func[i] = *aux;

    }

    for (int i = 0; i < 6; ++i) {
        auxVetFunc[i] = func[i].id;
    }

    while (position != sizeFileAux) {

        char partitionName[100];
        char str1[100] = "substitutionSelectionPartition";
        char str2[100];
        char str3[100] = ".dat";

        itoa(numberOfPartition,str2,10);
        strcat(strcpy(partitionName, str1), str2);
        strcat(strcpy(partitionName, partitionName), str3);

        FILE *filePartition = fopen(partitionName, "wb+");

        int auxVetFrozen[6] = {0, 0, 0, 0, 0, 0,};

        while (position != sizeFileAux) {

            smallElement = 9999999;

            for (int i = 0; i < 6; ++i) {

                if (smallElement > auxVetFunc[i] && auxVetFrozen[i] != 1) {
                    smallElement = auxVetFunc[i];
                    smallElementPosition = i;
                }
            }

            saveRegisterEmployee(&func[smallElementPosition], filePartition);

            fseek(file, position * sizeof(TFunc), SEEK_SET);

            TFunc *aux = readRegisterEmployee(file);

            position++;

            auxVetFunc[smallElementPosition] = aux->id;
            func[smallElementPosition] = *aux;

            if (aux->id < smallElement) {
                auxVetFrozen[smallElementPosition] = 1;
            }

            if(allVetFrozen(auxVetFrozen) == 1) {
                numberOfPartition++;
                break;
            }

        }

        fclose(filePartition);

        if (position >= sizeFileAux) {
            break;
        }

    }

    char partitionName[100];
    char str1[100] = "substitutionSelectionPartition";
    char str2[100];
    char str3[100] = ".dat";

    itoa(numberOfPartition,str2,10);
    strcat(strcpy(partitionName, str1), str2);
    strcat(strcpy(partitionName, partitionName), str3);

    FILE *filePartitionFinal = fopen(partitionName, "ab+");

    int k, j;

    struct Employee funcAux;

    for (k = 1; k < 6; k++) {

        for (j = 0; j < 6 - 1; j++) {

            if (func[j].id > func[j + 1].id) {
                funcAux = func[j];
                func[j] = func[j + 1];
                func[j + 1] = funcAux;
            }
        }
    }

    for (int i = 0; i < 6; ++i) {
        saveRegisterEmployee(&func[i], filePartitionFinal);
    }

    fclose(filePartitionFinal);

    for (int i = 0; i <= numberOfPartition; ++i) {


        itoa(i,str2,10);
        strcat(strcpy(partitionName, str1), str2);
        strcat(strcpy(partitionName, partitionName), str3);

        FILE *filePartition = fopen(partitionName, "rb+");

        printPartitionEmployeeID(filePartition, partitionName);

        fclose(filePartition);
    }

    mergeSort(numberOfPartition);

}