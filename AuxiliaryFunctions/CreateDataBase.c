//
// Created by diogoleite87 on 28/09/2022.
//

#include "Headers/employee.h"

void createDataBase(FILE *arq, int nFunc, int *vet) {
    for(int i = 1; i <= nFunc; i++) {

        printf("Creating random employee %i..\n", i);
        TFunc func;

        func.id = vet[i - 1];

        char auxName[15];
        for(int j = 0; j < 15; j++) {
            auxName[j]= 'a' + (char)(rand()%26);
        }

        sprintf(func.name, "%s", auxName);
        sprintf(func.cpf, "111.111.111-11");
        sprintf(func.birthDate, "01/08/2021");
        func.pay = 1000 + rand() % 10000;
        fseek(arq, (i-1)* sizeof(TFunc), SEEK_SET);
        saveRegisterEmployee(&func, arq);
    }
}