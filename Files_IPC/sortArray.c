#include <stdio.h>
#include <stdlib.h>

void swap(int *value1, int* value2){
    int temp = *value1;
    *(value1) = *(value2);
    *(value2) = temp;
}

void sortArray(int *array, int arraySize) {
    for (int i = 0; i < arraySize-1; i++) {
        for (int j = 0; j < arraySize-1-i; j++) {
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j+1]);
            }
        }
    }
}

void writeInFile(int* array,int arraySize, FILE* file){
    for (int i = 0; i < arraySize; i++) {
        fprintf(file, "%d ", array[i]);
    }
}

int* readFromFile(int arraySize, FILE* file){
    int *array = (int*)malloc(arraySize * sizeof(int));
    for (int i = 0; i < arraySize; i++) {
        fscanf(file, "%d", &array[i]);
    }
    return array;
}

FILE* openFile(char* fileMode){
    FILE *file = fopen("array.txt", fileMode);
    if (file == NULL) {
        perror("Error opening file");
    }
    return file;
}

int main() {
    FILE *file = openFile("r");

    int arraySize;
    fscanf(file, "%d", &arraySize);
    
    int *array = readFromFile(arraySize, file);
    
    fclose(file);

    sortArray(array, arraySize);

    file = openFile("w");
    
    writeInFile(array, arraySize, file);
    
    fclose(file);

    free(array);

    return 0;
}
