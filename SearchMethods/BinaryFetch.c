//
// Created by diogoleite87 on 28/09/2022.
//

#include "Headers/employee.h"

TFunc *binaryFetch(int id, FILE *file, int sizeFile, int *totalComparisons) {

    int left = 0, right = sizeFile - 1;

    rewind(file);

    while (left <= right) {
        int middle = (left+right) / 2;
        fseek(file, middle * sizeof(TFunc), SEEK_SET);
        TFunc *func = readRegisterEmployee(file);

        if (id == func -> id) {
            *totalComparisons += 1;
            return func;
        } else if (func->id < id) {
            *totalComparisons += 1;
            left = middle+1;
        } else {
            *totalComparisons += 1;
            right = middle-1;
        }
    }

    return NULL;
}