//
// Created by diogoleite87 on 28/09/2022.
//

#include "Headers/employee.h"

TFunc *readRegisterEmployee(FILE *in) {
    TFunc *func = (TFunc*) malloc (sizeof(TFunc));

    if ( 0 >= fread(&func->id, sizeof(int), 1, in)) {
        free(func);
        return NULL;
    }

    fread(func->name, sizeof(char), sizeof(func->name), in);
    fread(func->cpf, sizeof(char), sizeof(func->cpf), in);
    fread(func->birthDate, sizeof(char), sizeof(func->birthDate), in);
    fread(&func->pay, sizeof(double), 1, in);

    return func;
}