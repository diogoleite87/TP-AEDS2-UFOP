//
// Created by diogoleite87 on 28/09/2022.
//

#include "Headers/employee.h"

void binaryTreeOfWinners(int numberOfPartition, char nameFilePartition[]){

    int auxNumberOfPartition = numberOfPartition, flagAuxFinal = 0, auxTreeWinner = 0, sizeInTreeOfWinners;

    if (numberOfPartition % 2 == 0){
        sizeInTreeOfWinners = 2 * numberOfPartition - 1;
        auxNumberOfPartition--;
    }
    else {
        sizeInTreeOfWinners = 2 * numberOfPartition;
    }

    int aux = sizeInTreeOfWinners - 1;

    TVetFile *listFile = calloc(sizeof(*listFile), numberOfPartition);
    TFunc *smallElement = calloc(sizeof(*smallElement), 1);
    TFunc **funcAux = calloc(sizeof(**funcAux), sizeInTreeOfWinners);
    for (int i = 0; i < auxNumberOfPartition; i++) funcAux[i] = calloc(sizeof(TFunc), 1);

    FILE *fileBinaryOfTreeSorted = fopen("binaryOfTreeFileSorted.dat", "wb+");

    for (int i = 0; i < numberOfPartition; i++){
        listFile[i].init_p = 0;

        char partitionName[100];
        char str1[100];
        char str2[100] = ".dat";

        itoa(i, str1, 10);
        strcat(strcpy(partitionName, nameFilePartition), str1);
        strcat(strcpy(partitionName, partitionName), str2);

        listFile[i].filePartition = fopen (partitionName, "rb+");
        fseek(listFile[i].filePartition, 0 * sizeof(TFunc), SEEK_SET);

        if (aux+1 >= numberOfPartition){
            funcAux[aux] = readRegisterEmployee(listFile[i].filePartition);
            aux--;
        }
        listFile[i].end_p = 0;
    }

    treeWinner(funcAux, fileBinaryOfTreeSorted, sizeInTreeOfWinners, &auxTreeWinner);

    while (flagAuxFinal < numberOfPartition){
        aux = sizeInTreeOfWinners - 1;

        for (int i = 0; i < numberOfPartition; i++){

            if (fgetc(listFile[i].filePartition) == EOF && listFile[i].end_p == 0 && smallElement->id == funcAux[aux]->id){
                flagAuxFinal++;
                listFile[i].end_p = 1;
                i--;

                if (flagAuxFinal == numberOfPartition) {
                    break;
                }

                for (int j = 0; j < sizeInTreeOfWinners; j++){
                    if (funcAux[j]->id == smallElement->id) funcAux[j]->id = 15000;
                }

                treeWinner(funcAux, fileBinaryOfTreeSorted, sizeInTreeOfWinners, &auxTreeWinner);
            } else {
                *smallElement = *funcAux[0];

                if (smallElement->id == funcAux[aux]->id && listFile[i].end_p == 0){
                    listFile[i].init_p += 1;

                    if (fgetc(listFile[i].filePartition) != EOF){
                        fseek (listFile[i].filePartition, listFile[i].init_p * sizeof(TFunc), SEEK_SET);
                        free(funcAux[aux]);
                        funcAux[aux] = readRegisterEmployee(listFile[i].filePartition);
                        treeWinner(funcAux, fileBinaryOfTreeSorted, sizeInTreeOfWinners, &auxTreeWinner);
                    }
                }
                aux--;
            }
        }
    }

    for (int i = 0; i < numberOfPartition; i++) {
        fclose(listFile[i].filePartition);
    }

    for (int i = 0; i < sizeInTreeOfWinners; i++){
        free(funcAux[i]);
    }

    free(funcAux);
    free(smallElement);
    free(listFile);
    fclose(fileBinaryOfTreeSorted);

}