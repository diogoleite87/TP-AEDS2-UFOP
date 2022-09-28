//
// Created by diogoleite87 on 28/09/2022.
//

#include "Headers/employee.h"

int allVetFrozen (int vet[6]) {

    int cont = 0;

    for (int i = 0; i < 6; ++i) {
        if (vet[i] == 1) {
            cont++;
        }
    }

    if (cont == 6) {
        return 1;
    } else {
        return 0;
    }
}