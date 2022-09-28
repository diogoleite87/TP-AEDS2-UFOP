//
// Created by diogoleite87 on 28/09/2022.
//

#include "Headers/employee.h"

TFunc *sequentialFetch(int id, FILE *file, int *totalComparisons) {
    int position = 0;

    while (!feof(file)) {

        fseek(file, position * sizeof(TFunc), SEEK_SET) ;
        TFunc *func = readRegisterEmployee(file);

        position++;

        if (func == NULL) {
            *totalComparisons += 1;
            return NULL;
        } else if (id == func->id) {
            *totalComparisons += 1;
            return func;
        } else {
            *totalComparisons += 1;
        }

    }

    return NULL;
}