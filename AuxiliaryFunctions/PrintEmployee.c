//
// Created by diogoleite87 on 28/09/2022.
//

#include "Headers/employee.h"

void printEmployee (TFunc *func) {
    printf("\nRegister found: \n");
    printf("ID: %d\n", func->id);
    printf("Name: %s\n", func->name);
    printf("CPF: %s\n", func->cpf);
    printf("Birth of Date: %s\n", func->birthDate);
    printf("Payment: %.2f\n", func->pay);
}