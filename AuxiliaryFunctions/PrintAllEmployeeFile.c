//
// Created by diogoleite87 on 29/09/2022.
//

#include "Headers/employee.h"

void printAllEmployeeFile(FILE *file) {

    rewind(file);

    for (int i = 0; i < sizeFile(file, 0); ++i) {

        fseek(file, i * sizeof(TFunc), SEEK_SET);
        TFunc *func = readRegisterEmployee(file);
        printEmployee(func);
    }

}