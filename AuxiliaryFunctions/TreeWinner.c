//
// Created by diogoleite87 on 30/09/2022.
//

#include "Headers/employee.h"

void treeWinner(TFunc **func, FILE *file, int sizeInTreeOfWinners, int *auxTreeWinner) {

    int aux;

    for (int i = sizeInTreeOfWinners - 1; i > 0; i--){

        if (i % 2 != 0 && i == sizeInTreeOfWinners - 1){
            aux = (i - 1) / 2;
            *func[aux] = *func[i];
        }
        else{
            if (i % 2 == 0 && func[i]->id < func[i-1]->id){
                aux = (i - 2) / 2;
                *func[aux] = *func[i];
            }
            else if (i % 2 == 0 && func[i-1]->id < func[i]->id){
                aux = (i - 2) / 2;
                *func[aux] = *func[i - 1];
            }
        }
    }

    saveRegisterEmployee(func[0], file);
    *auxTreeWinner +=1;
}