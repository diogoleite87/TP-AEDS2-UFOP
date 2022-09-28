//
// Created by diogoleite87 on 28/09/2022.
//

#include "Headers/employee.h"

TFunc *insertionSort(FILE *file, int sizeFile) {

    rewind(file);
    int i;

    for (int j = 2; j <= sizeFile; j++) {

        fseek(file, (j - 1) * sizeof(TFunc), SEEK_SET);
        TFunc *auxJ = readRegisterEmployee(file);

        i = j - 1;
        fseek(file, (i - 1) * sizeof(TFunc), SEEK_SET);
        do{
            TFunc *auxI = readRegisterEmployee(file);
            if( (auxI->id < auxJ->id)){
                break;
            }

            fseek(file, i * sizeof(TFunc), SEEK_SET);

            saveRegisterEmployee(auxI, file);
            i = i - 1;
            fseek(file, (i - 1) * sizeof(TFunc), SEEK_SET);

            free(auxI);

        }while ((i > 0) );

        fseek(file, (i) * sizeof(TFunc), SEEK_SET);
        saveRegisterEmployee(auxJ, file);
        free(auxJ);
    }

    fflush(file);
}
