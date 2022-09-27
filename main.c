#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "employee.h"

void saveRegisterEmployee(TFunc *func, FILE *out) {
    fwrite(&func->id, sizeof(int), 1, out);
    fwrite(func->name, sizeof(char), sizeof(func->name), out);
    fwrite(func->cpf, sizeof(char), sizeof(func->cpf), out);
    fwrite(func->birthDate, sizeof(char), sizeof(func->birthDate), out);
    fwrite(&func->pay, sizeof(double), 1, out);
}

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

void shuffleVet(int *vet, int vetSize)
{

    for (int i = 0; i < vetSize; i++) {
        vet[i] = i + 1;
    }

    for (int i = 0; i < vetSize; i++)
    {
        int r = rand() % vetSize;

        int temp = vet[i];
        vet[i] = vet[r];
        vet[r] = temp;
    }

}

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

TFunc *binaryFetch(int id, FILE *file, int sizeFile, int *totalComparisons) {

    int left = 0, right = sizeFile - 1;

    rewind(file);

    while (left <= right) {
        int middle = (left+right) / 2;
        fseek(file, middle * sizeof(TFunc), SEEK_SET);
        TFunc *func = readRegisterEmployee(file);

        if (id == func -> id) {
            *totalComparisons += 1;
            return func;
        } else if (func->id < id) {
            *totalComparisons += 1;
            left = middle+1;
        } else {
            *totalComparisons += 1;
            right = middle-1;
        }
    }

    return NULL;
}

void printEmployee (TFunc *func) {
    printf("\nRegister found: \n");
    printf("ID: %d\n", func->id);
    printf("Name: %s\n", func->name);
    printf("CPF: %s\n", func->cpf);
    printf("Birth of Date: %s\n", func->birthDate);
    printf("Payment: %.2f\n", func->pay);
}

TFunc *sequentialFetch(int id, FILE *file, int *totalComparisons) {
    int position = 0;

    while (!feof(file)) {

        fseek(file, position * sizeof(TFunc), SEEK_SET) ;
        TFunc *func = readRegisterEmployee(file);

        position++;

        if (func == NULL) {
            *totalComparisons += 1;
            return NULL;
        } else if (id == func->id) {
            *totalComparisons += 1;
            return func;
        } else {
            *totalComparisons += 1;
        }

    }

    return NULL;
}

TFunc *insertionSort(FILE *file, int sizeFile) {

    printf("\nSorting with Insertion Sort...");
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

TFunc *keySort(FILE *file, FILE *sortedFile, int sizeFile) {
    printf("\nSorting for KeySort...");


    rewind(file);

    struct KeyID keys[sizeFile];
    int position = 0;

    while (position < sizeFile){

        fseek(file, position * sizeof(TFunc), SEEK_SET);

        keys[position].RRN = ftell(file);

        TFunc *func = readRegisterEmployee(file);

        keys[position].id = func->id;

        position++;
    }

    int i, j;
    struct KeyID aux;

    for (i=0; i< sizeFile; i++) {
        for (j=i+1; j< sizeFile; j++) {
            if (keys[i].id > keys[j].id) {
                aux = keys[i];
                keys[i] = keys[j];
                keys[j] = aux;
            }
        }
    }

    rewind(file);

    for(int k = 0; k < sizeFile; ++k) {

        fseek(file, keys[k].RRN, SEEK_SET);
        TFunc *aux1 = readRegisterEmployee(file);

        fseek(sortedFile, k * sizeof(TFunc), SEEK_SET);
        saveRegisterEmployee(aux1, sortedFile);
    }

}

int sizeFile(FILE *file, int contSizeFile) {

    int cont = 0;
    int bytesAUX = 0;
    char c, auxC = '\n';

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

TFunc *printPartitionEmployeeID(FILE *file, char partitionName[]) {

    printf("\nIDs employee of partition %s: \n --->  ", partitionName);

    for (int i = 0; i < sizeFile(file, 0); ++i) {

        fseek(file, i * sizeof(TFunc), SEEK_SET) ;
        TFunc *aux = readRegisterEmployee(file);

        printf(" %i ", aux->id);
    }

    printf("\n");
}

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

TFunc *substitutionSelection (FILE *file) {

    int numberOfPartition = 0, contSizeFile = 0, position = 5, smallElementPosition = 0, smallElement = 999999, sizeFileAux = 0, selectedPosition = 0;
    struct Employee func[6];
    int auxVetFunc [6] = {0, 0, 0, 0, 0, 0};

    rewind(file);

    sizeFileAux = sizeFile(file, contSizeFile);


    printf("\nPerforming substitution selection...");

    for (int i = 0; i < 6; ++i) {
        fseek(file, i * sizeof(TFunc), SEEK_SET);

        TFunc *aux = readRegisterEmployee(file);
        func[i] = *aux;

    }

    for (int i = 0; i < 6; ++i) {
        auxVetFunc[i] = func[i].id;
    }

    while (position != sizeFileAux) {

        char partitionName[100];
        char str1[100] = "substitutionSelectionPartition";
        char str2[100];
        char str3[100] = ".dat";

        itoa(numberOfPartition,str2,10);
        strcat(strcpy(partitionName, str1), str2);
        strcat(strcpy(partitionName, partitionName), str3);

        FILE *filePartition = fopen(partitionName, "wb+");

        int auxVetFrozen[6] = {0, 0, 0, 0, 0, 0,};

        while (position != sizeFileAux) {

            smallElement = 9999999;

            for (int i = 0; i < 6; ++i) {

                if (smallElement > auxVetFunc[i] && auxVetFrozen[i] != 1) {
                    smallElement = auxVetFunc[i];
                    smallElementPosition = i;
                }
            }

            saveRegisterEmployee(&func[smallElementPosition], filePartition);

            fseek(file, position * sizeof(TFunc), SEEK_SET);

            TFunc *aux = readRegisterEmployee(file);

            auxVetFunc[smallElementPosition] = aux->id;
            func[smallElementPosition] = *aux;

            if (aux->id < smallElement) {
                auxVetFrozen[smallElementPosition] = 1;
            }


            if(allVetFrozen(auxVetFrozen) == 1) {
                numberOfPartition++;
                break;
            }

            position++;
        }

        fclose(filePartition);

        if (position >= sizeFileAux) {
            break;
        }

    }

    for (int i = 0; i <= numberOfPartition; ++i) {

        char partitionName[100];
        char str1[100] = "substitutionSelectionPartition";
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

TFunc *naturalSelection (FILE *file) {

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

int main() {
    printf("Starting...\n");

    int pick;

    printf("\nEnter an option: \n 1 - Create random .dat file; \n 2 - Read existing .dat file.\n   ---> ");
    scanf("%i", &pick);

    if (pick == 1) {
        FILE *file = fopen("register.dat", "wb+");

        if (file != NULL) {

            int numFunc = 0, idEmployee = 0, sortingMethod = 0;
            int *vet, totalComparisonsSequential = 0, totalComparisonsBinaryFetch = 0;
            double timeSpentDefault = 0.0, timeSpentBinaryFetch = 0.0;

            printf("Input the total number of employees: ");
            scanf("%i", &numFunc);

            printf("Input the id of Employee you want to find: ");
            scanf("%i", &idEmployee);

            vet = (int *)malloc(numFunc * sizeof(int));

            shuffleVet(vet, numFunc);

            createDataBase(file, numFunc, vet);

            clock_t begin = clock();

            TFunc *func = sequentialFetch(idEmployee, file, &totalComparisonsSequential);

            clock_t end = clock();
            timeSpentDefault += (double)(end - begin) / CLOCKS_PER_SEC;

            if (func == NULL) {
                printf("\nRegister not found.\n");
            } else {
                printf("\nRecord found in sequential: \n");
                printEmployee(func);
            }

            printf("\nInput Sorting method: \n 1 - InsertionSort;\n 2 - KeySort;\n 3 - Substitution Selection;\n 4 - Natural Selection.\n --->  ");
            scanf("%i", &sortingMethod);

            if (sortingMethod == 1) {
                insertionSort(file, numFunc);

                printf("\nPerforming binary search...");

                clock_t beginBinary = clock();

                TFunc *funcBinaryFetch = binaryFetch(idEmployee, file, numFunc, &totalComparisonsBinaryFetch);

                clock_t endBinary = clock();
                timeSpentBinaryFetch += (double)(endBinary - beginBinary) / CLOCKS_PER_SEC;

                if (funcBinaryFetch == NULL) {
                    printf("\nRegister not found.\n");
                } else {
                    printf("\nRecord found in Binary Fetch: \n");
                    printEmployee(funcBinaryFetch);
                }

            } else if (sortingMethod == 2) {

                FILE *sortedFile = fopen("sortedRegister.dat", "wb+");

                double timeSpentKeySort = 0.0;

                clock_t beginKeySort = clock();

                keySort(file, sortedFile, numFunc);

                clock_t endKeySort = clock();
                timeSpentKeySort += (double)(endKeySort - beginKeySort) / CLOCKS_PER_SEC;

                clock_t beginBinary = clock();

                TFunc *funcBinaryFetch = binaryFetch(idEmployee, sortedFile, numFunc, &totalComparisonsBinaryFetch);

                clock_t endBinary = clock();
                timeSpentBinaryFetch += (double)(endBinary - beginBinary) / CLOCKS_PER_SEC;

                if (funcBinaryFetch == NULL) {
                    printf("\nRegister not found.\n");
                } else {
                    printf("\nRecord found in Binary Fetch in KeySort: \n");
                    printEmployee(func);
                }

                printf("\nThe elapsed time sorting KeySort: %f\n", timeSpentKeySort);

                fclose(sortedFile);
            } else if (sortingMethod == 3){
                substitutionSelection(file);

                fclose(file);

                exit(1);
            } else {
                naturalSelection(file);

                fclose(file);

                exit(1);
            }

            printf("\nThe elapsed time in sequential fetch is %f seconds.\n", timeSpentDefault);
            printf("Total of comparisons in sequential fetch: %i.\n", totalComparisonsSequential);

            printf("\nThe elapsed time in Binary Fetch is %f seconds.\n", timeSpentBinaryFetch);
            printf("Total of comparisons in Binary Fetch: %i.\n", totalComparisonsBinaryFetch);

            free(func);
            free(vet);
            fclose(file);

        } else {
            printf("Err file.\n");
            return 1;
        }
    } else {

        char nameFile[50];

        printf("\nEnter the file name: ");
        scanf("%s", &nameFile);

        FILE *file = fopen(nameFile, "rb+");

        if (file != NULL) {

            int idEmployee, totalComparisonsSequential = 0, sortingMethod = 0, totalComparisonsBinaryFetch = 0;
            double timeSpentDefault = 0.0, timeSpentBinaryFetch = 0.0;;

            printf("\nOk!\n");

            printf("Input the id of Employee you want to find: ");
            scanf("%i", &idEmployee);

            clock_t begin = clock();

            TFunc *func = sequentialFetch(idEmployee, file, &totalComparisonsSequential);

            clock_t end = clock();
            timeSpentDefault += (double)(end - begin) / CLOCKS_PER_SEC;

            if (func == NULL) {
                printf("\nRegister not found.\n");
            } else {
                printf("\nRecord found in sequential: \n");
                printEmployee(func);
            }

            printf("\nInput Sorting method: \n 1 - InsertionSort;\n 2 - KeySort;\n 3 - Substitution Selection;\n 4 - Natural Selection.\n --->  ");
            scanf("%i", &sortingMethod);

            if (sortingMethod == 1) {

                int contSizeFile = 0;
                contSizeFile = sizeFile(file, contSizeFile);

                insertionSort(file, contSizeFile);

                printf("\nPerforming binary search...");

                clock_t beginBinary = clock();


                TFunc *funcBinaryFetch = binaryFetch(idEmployee, file, contSizeFile, &totalComparisonsBinaryFetch);

                clock_t endBinary = clock();
                timeSpentBinaryFetch += (double)(endBinary - beginBinary) / CLOCKS_PER_SEC;

                if (funcBinaryFetch == NULL) {
                    printf("\nRegister not found.\n");
                } else {
                    printf("\nRecord found in Binary Fetch: \n");
                    printEmployee(funcBinaryFetch);
                }

            } else if (sortingMethod == 2){

                FILE *sortedFile = fopen("sortedRegister.dat", "wb+");

                int contSizeFile = 0;
                contSizeFile = sizeFile(file, contSizeFile);

                double timeSpentKeySort = 0.0;

                clock_t beginKeySort = clock();

                keySort(file, sortedFile, contSizeFile);

                clock_t endKeySort = clock();
                timeSpentKeySort += (double)(endKeySort - beginKeySort) / CLOCKS_PER_SEC;

                clock_t beginBinary = clock();


                TFunc *funcBinaryFetch = binaryFetch(idEmployee, sortedFile, contSizeFile, &totalComparisonsBinaryFetch);

                clock_t endBinary = clock();
                timeSpentBinaryFetch += (double)(endBinary - beginBinary) / CLOCKS_PER_SEC;

                if (funcBinaryFetch == NULL) {
                    printf("\nRegister not found.\n");
                } else {
                    printf("\nRecord found in Binary Fetch in KeySort: \n");
                    printEmployee(func);
                }

                printf("\nThe elapsed time sorting KeySort: %f\n", timeSpentKeySort);

                fclose(sortedFile);
            } else if (sortingMethod == 3){
                substitutionSelection(file);

                fclose(file);

                exit(1);
            } else {
                naturalSelection(file);

                fclose(file);

                exit(1);
            }

            printf("\nThe elapsed time in Sequential Fetch is %f seconds.\n", timeSpentDefault);
            printf("Total of comparisons in Sequential Fetch: %i.\n", totalComparisonsSequential);

            printf("\nThe elapsed time in Binary Fetch is %f seconds.\n", timeSpentBinaryFetch);
            printf("Total of comparisons in Binary Fetch: %i.\n", totalComparisonsBinaryFetch);

            free(func);
            fclose(file);

        } else {
            printf("Err file.\n");
            return 1;
        }
    }

    return 0;
}
