//
// Created by diogoleite87 on 28/09/2022.
//

#include "Headers/employee.h"

int sizeFile(FILE *file, int contSizeFile) {

    int bytesAUX = 0;

    while(!feof(file)) {

        fseek(file, bytesAUX * sizeof(TFunc), SEEK_SET);

        TFunc *aux = readRegisterEmployee(file);
        if(aux != NULL) {
            contSizeFile++;
        }

        bytesAUX++;
    }

    return contSizeFile;
}