#include "Headers/employee.h"

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

            printf("\nInput Sorting method: \n 1 - InsertionSort;\n 2 - KeySort;\n 3 - Substitution Selection and MergeSort;\n 4 - Natural Selection and Binary Tree Of Winners;\n  --->  ");
            scanf("%i", &sortingMethod);

            if (sortingMethod == 1) {

                printf("\nSorting with Insertion Sort...");

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

                printf("\nThe elapsed time sorting KeySort: %filePartition\n", timeSpentKeySort);

                fclose(sortedFile);
            } else if (sortingMethod == 3){

                int numberOfPartition = 0;
                numberOfPartition = substitutionSelection(file, "substitutionSelectionPartition");
                mergeSort(numberOfPartition, "substitutionSelectionPartition");

                fclose(file);

                return 0;
            } else if (sortingMethod == 4){
                int numberOfPartition = 1;
                numberOfPartition += naturalSelection(file, "naturalSelectionPartition");
                binaryTreeOfWinners(numberOfPartition, "naturalSelectionPartition");

                FILE *fileBinaryOfTreeSorted = fopen("binaryOfTreeFileSorted.dat","rb+");

                printPartitionEmployeeID(fileBinaryOfTreeSorted, "binaryOfTreeFileSorted.dat");

                fclose(fileBinaryOfTreeSorted);
                fclose(file);

                return 0;
            } else {

                int numberOfPartition;
                char partitionName[100];
                char str1[100];
                char str2[100] = ".dat";

                printf("\nInsert number of partition for Hash Table (Hash Function): ");
                scanf("%i", &numberOfPartition);

                makePartitionHashTable(numberOfPartition);
                hashTable(file, numberOfPartition, numFunc);

                printf("Hash Table Successfully Created");

                int flagAux = 0;

                while (flagAux != 5) {

                    printf("\n\nInput an option: \n 1 - Insert employee; \n 2 - Search Employee; \n 3 - Delete employee; \n 4 - Print employee IDs; \n 5 - Close program. \n ----> ");
                    scanf("%i", &flagAux);

                    if (flagAux == 1) {
                        int employeeID;
                        int partitionID;

                        printf("\nInput employee ID: ");
                        scanf("%i", &employeeID);

                        TFunc funcHashIsert;

                        if (employeeID < 0)
                        {
                            printf("\nErr: ID < 0");
                            break;
                        }

                        funcHashIsert.id = employeeID;

                        char auxName[15];
                        for (int j = 0; j < 15; j++)
                        {
                            auxName[j] = 'a' + (char)(rand() % 26);
                        }

                        sprintf(funcHashIsert.name, "%s", auxName);
                        sprintf(funcHashIsert.cpf, "111.111.111-11");
                        sprintf(funcHashIsert.birthDate, "01/08/2021");
                        funcHashIsert.pay = 1000 + rand() % 10000;

                        partitionID = employeeID % numberOfPartition;

                        insertHashTable(&funcHashIsert, employeeID, partitionID);


                    } else if (flagAux == 2) {

                        int employeeID;
                        int partitionID;

                        printf("\nInput employee id: ");
                        scanf("%i", &employeeID);

                        partitionID = employeeID % numberOfPartition;

                        TFunc *funcSearchHashTable = searchHashTable(employeeID, partitionID);

                        if (funcSearchHashTable != NULL) {
                            printEmployee(funcSearchHashTable);
                        } else {
                            printf("\nEmployee id not found");
                        }

                    } else if (flagAux == 3) {

                        int employeeID;
                        int partitionID;

                        printf("\nInput employee id: ");
                        scanf("%i", &employeeID);

                        partitionID = employeeID % numberOfPartition;

                        deleteHashTable(employeeID, partitionID);

                    } else if (flagAux == 4) {

                        for (int i = 0; i < numberOfPartition; ++i) {

                            itoa(i, str1, 10);
                            strcat(strcpy(partitionName, "hashTablePartition"), str1);
                            strcat(strcpy(partitionName, partitionName), str2);

                            FILE *filePartition = fopen(partitionName,"rb+");

                            printPartitionEmployeeID(filePartition, partitionName);

                            fclose(filePartition);
                        }

                    } else {
                        printf("Closing...");
                    }
                }

                fclose(file);
                return 0;
            }

            printf("\nThe elapsed time in sequential fetch is %filePartition seconds.\n", timeSpentDefault);
            printf("Total of comparisons in sequential fetch: %i.\n", totalComparisonsSequential);

            printf("\nThe elapsed time in Binary Fetch is %filePartition seconds.\n", timeSpentBinaryFetch);
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
            double timeSpentDefault = 0.0, timeSpentBinaryFetch = 0.0;

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

            printf("\nInput Sorting method: \n 1 - InsertionSort;\n 2 - KeySort;\n 3 - Substitution Selection and MergeSort;\n 4 - Natural Selection and Binary Tree Of Winners;\n 5 - Hash Table.\n  --->  ");
            scanf("%i", &sortingMethod);

            if (sortingMethod == 1) {

                int contSizeFile = 0;
                contSizeFile = sizeFile(file, contSizeFile);

                printf("\nSorting with Insertion Sort...");

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

                printf("\nThe elapsed time sorting KeySort: %filePartition\n", timeSpentKeySort);

                fclose(sortedFile);
            } else if (sortingMethod == 3){
                int numberOfPartition = 0;
                numberOfPartition = substitutionSelection(file, "substitutionSelectionPartition");
                mergeSort(numberOfPartition, "substitutionSelectionPartition");

                fclose(file);

                return 0;
            } else if (sortingMethod == 4) {
                int numberOfPartition = 1;
                numberOfPartition += naturalSelection(file, "naturalSelectionPartition");
                binaryTreeOfWinners(numberOfPartition, "naturalSelectionPartition");

                FILE *fileBinaryOfTreeSorted = fopen("binaryOfTreeFileSorted.dat","rb+");

                printPartitionEmployeeID(fileBinaryOfTreeSorted, "binaryOfTreeFileSorted.dat");

                fclose(fileBinaryOfTreeSorted);
                fclose(file);

                return 0;
            } else {

                int numberOfPartition;
                int contSizeFile = 0;
                contSizeFile = sizeFile(file, contSizeFile);
                char partitionName[100];
                char str1[100];
                char str2[100] = ".dat";

                printf("\nInsert number of partition for Hash Table (Hash Function): ");
                scanf("%i", &numberOfPartition);

                makePartitionHashTable(numberOfPartition);
                hashTable(file, numberOfPartition, contSizeFile);

                printf("Hash Table Successfully Created");

                int flagAux = 0;

                while (flagAux != 5) {

                    printf("\n\nInput an option: \n 1 - Insert employee; \n 2 - Search Employee; \n 3 - Delete employee; \n 4 - Print employee IDs; \n 5 - Close program. \n ----> ");
                    scanf("%i", &flagAux);

                    if (flagAux == 1) {
                        int employeeID;
                        int partitionID;

                        printf("\nInput employee ID: ");
                        scanf("%i", &employeeID);

                        TFunc funcHashIsert;

                        if (employeeID < 0)
                        {
                            printf("\nErr: ID < 0");
                            break;
                        }

                        funcHashIsert.id = employeeID;

                        char auxName[15];
                        for (int j = 0; j < 15; j++)
                        {
                            auxName[j] = 'a' + (char)(rand() % 26);
                        }

                        sprintf(funcHashIsert.name, "%s", auxName);
                        sprintf(funcHashIsert.cpf, "111.111.111-11");
                        sprintf(funcHashIsert.birthDate, "01/08/2021");
                        funcHashIsert.pay = 1000 + rand() % 10000;

                        partitionID = employeeID % numberOfPartition;

                        insertHashTable(&funcHashIsert, employeeID, partitionID);


                    } else if (flagAux == 2) {

                        int employeeID;
                        int partitionID;

                        printf("\nInput employee id: ");
                        scanf("%i", &employeeID);

                        partitionID = employeeID % numberOfPartition;

                        TFunc *funcSearchHashTable = searchHashTable(employeeID, partitionID);

                        if (funcSearchHashTable != NULL) {
                            printEmployee(funcSearchHashTable);
                        } else {
                            printf("\nEmployee id not found");
                        }

                    } else if (flagAux == 3) {

                        int employeeID;
                        int partitionID;

                        printf("\nInput employee id: ");
                        scanf("%i", &employeeID);

                        partitionID = employeeID % numberOfPartition;

                        deleteHashTable(employeeID, partitionID);

                    } else if (flagAux == 4) {

                        for (int i = 0; i < numberOfPartition; ++i) {

                            itoa(i, str1, 10);
                            strcat(strcpy(partitionName, "hashTablePartition"), str1);
                            strcat(strcpy(partitionName, partitionName), str2);

                            FILE *filePartition = fopen(partitionName,"rb+");

                            printPartitionEmployeeID(filePartition, partitionName);

                            fclose(filePartition);
                        }

                    } else {
                        printf("Closing...");
                    }
                }

                fclose(file);
                return 0;

            }

            printf("\nThe elapsed time in Sequential Fetch is %filePartition seconds.\n", timeSpentDefault);
            printf("Total of comparisons in Sequential Fetch: %i.\n", totalComparisonsSequential);

            printf("\nThe elapsed time in Binary Fetch is %filePartition seconds.\n", timeSpentBinaryFetch);
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
