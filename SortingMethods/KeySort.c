//
// Created by diogoleite87 on 28/09/2022.
//

#include "Headers/employee.h"

void keySort(FILE *file, FILE *sortedFile, int sizeFile) {
    printf("\nSorting for KeySort...");


    rewind(file);

    struct KeyID keys[sizeFile];
    int position = 0;

    while (position < sizeFile){

        fseek(file, position * sizeof(TFunc), SEEK_SET);

        keys[position].RRN = ftell(file);

        TFunc *func = readRegisterEmployee(file);

        keys[position].id = func->id;

        position++;
    }

    int i, j;
    struct KeyID aux;

    for (i=0; i< sizeFile; i++) {
        for (j=i+1; j< sizeFile; j++) {
            if (keys[i].id > keys[j].id) {
                aux = keys[i];
                keys[i] = keys[j];
                keys[j] = aux;
            }
        }
    }

    rewind(file);

    for(int k = 0; k < sizeFile; ++k) {

        fseek(file, keys[k].RRN, SEEK_SET);
        TFunc *aux1 = readRegisterEmployee(file);

        fseek(sortedFile, k * sizeof(TFunc), SEEK_SET);
        saveRegisterEmployee(aux1, sortedFile);
    }

}