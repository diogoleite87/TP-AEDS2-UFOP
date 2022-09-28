//
// Created by diogoleite87 on 28/09/2022.
//

#include "Headers/employee.h"

void saveRegisterEmployee(TFunc *func, FILE *out) {
    fwrite(&func->id, sizeof(int), 1, out);
    fwrite(func->name, sizeof(char), sizeof(func->name), out);
    fwrite(func->cpf, sizeof(char), sizeof(func->cpf), out);
    fwrite(func->birthDate, sizeof(char), sizeof(func->birthDate), out);
    fwrite(&func->pay, sizeof(double), 1, out);
}
