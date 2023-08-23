#include <stdio.h>
#include <stdlib.h>

FILE* openFile(char* fileMode){
    FILE *file = fopen("array.txt", fileMode);
    if (file == NULL) {
        perror("Error opening file");
    }
    return file;
}

void writeInFile(int* array,int arraySize, FILE* file){
    for (int i = 0; i < arraySize; i++) {
        fprintf(file, "%d ", array[i]);
    }
}

void readFromFile(FILE* file){
    int value;
    while (fscanf(file, "%d", &value) != -1) {
        printf("%d ", value);
    }
}

int main() {
    FILE *file = openFile("w");

    printf("Enter the Size of array : ");
    int arraySize;
    scanf("%d", &arraySize);
    fprintf(file, "%d\n", arraySize);

    printf("Enter the Numbers : ");
    int array[arraySize];
    for (int i = 0; i < arraySize; i++) {
        scanf("%d", &array[i]);
    }
    writeInFile(array, arraySize, file);
    
    fclose(file);

    system("./sortArray");

    file = openFile("r");

    printf("Sorted Array : ");
    readFromFile(file);
    
    fclose(file);

    return 0;
}
