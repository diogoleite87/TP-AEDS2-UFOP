//
// Created by diogoleite87 on 28/09/2022.
//

#include "Headers/employee.h"

void naturalSelection (FILE *file) {

    int  sizeFileAux = sizeFile(file, 0), position = 0, numberOfPartition = 0, smallElement = 999999999, smallElementPosition = 0, sizeReservoir = 0, flag = 0;

    struct Employee func[6];

    int auxFuncVet[6] = {0, 0, 0, 0, 0, 0};

    rewind(file);

    printf("\nPerforming substitution selection...");

    while (!feof(file)) {

        FILE *fileReservoir = fopen("reservoir.dat", "wb+");

        char partitionName[100];
        char str1[100] = "naturalSelectionPartition";
        char str2[100];
        char str3[100] = ".dat";

        itoa(numberOfPartition,str2,10);
        strcat(strcpy(partitionName, str1), str2);
        strcat(strcpy(partitionName, partitionName), str3);

        FILE *filePartition = fopen(partitionName, "wb+");

        if (flag == 0) {
            for (int i = 0; i < 6; ++i) {

                TFunc *auxFunc = readRegisterEmployee(file);
                position++;

                func[i] = *auxFunc;
                auxFuncVet[i] = auxFunc->id;
            }
        }

        while (!feof(file)) {

            for (int i = 0; i < 6; ++i) {

                if (auxFuncVet[i] < smallElement) {
                    smallElement = auxFuncVet[i];
                    smallElementPosition = i;
                }
            }

            TFunc *auxFunc = readRegisterEmployee(file);
            position++;


            if (auxFunc->id < func[smallElementPosition].id) {
                saveRegisterEmployee(auxFunc, fileReservoir);
                sizeReservoir++;

                if (sizeReservoir == 6) {

                    break;
                }

            } else {
                saveRegisterEmployee(&func[smallElementPosition], filePartition);
                auxFuncVet[smallElementPosition] = auxFunc->id;
                func[smallElementPosition] = *auxFunc;
            }

            smallElement = 999999999;

            if (position >= sizeFileAux) {
                break;
            }

        }

        struct Employee aux;

        int k, j;

        for (k = 1; k < 6; k++) {

            for (j = 0; j < 6 - 1; j++) {

                if (func[j].id > func[j + 1].id) {
                    aux = func[j];
                    func[j] = func[j + 1];
                    func[j + 1] = aux;
                }
            }
        }

        for (int i = 0; i < 6; ++i) {
            saveRegisterEmployee(&func[i], filePartition);
        }

        rewind(fileReservoir);

        for (int i = 0; i < sizeReservoir; ++i) {
            TFunc *auxFuncReservoir = readRegisterEmployee(fileReservoir);
            func[i] = *auxFuncReservoir;
            auxFuncVet[i] = auxFuncReservoir->id;
            flag = 1;
        }


        fclose(fileReservoir);
        fclose(filePartition);

        if (position >= sizeFileAux) {
            break;
        }

        sizeReservoir = 0;
        numberOfPartition++;

    }

    for (int i = 0; i <= numberOfPartition; ++i) {

        char partitionName[100];
        char str1[100] = "naturalSelectionPartition";
        char str2[100];
        char str3[100] = ".dat";

        itoa(i,str2,10);
        strcat(strcpy(partitionName, str1), str2);
        strcat(strcpy(partitionName, partitionName), str3);

        FILE *filePartition = fopen(partitionName, "rb+");

        printPartitionEmployeeID(filePartition, partitionName);

        fclose(filePartition);
    }
}
