#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

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

void printArray(int* array, int arraySize){
    for (int index = 0; index < arraySize; index++)
    {
        printf("%d ", array[index]);
    }
}

int main()
{
    printf("Enter the Size of array: ");
    int arraySize;
    scanf("%d", &arraySize);

    int *array = (int*)malloc(arraySize*sizeof(int));

    printf("Enter elements of array: \n");
    for (int index = 0; index < arraySize; index++)
    {
        scanf("%d", &array[index]);
    }

    int pipe_fd[2];

    if (pipe(pipe_fd) == -1)
    {
        perror("Pipe creation failed");
        return -1;
    }

    write(pipe_fd[1], &arraySize, sizeof(arraySize));
    write(pipe_fd[1], array, arraySize*sizeof(array));

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("Fork failed");
        return -1;
    }
    else if(pid == 0)
    {
        read(pipe_fd[0], &arraySize, sizeof(arraySize));
        read(pipe_fd[0], array, arraySize*sizeof(array));

        close(pipe_fd[0]);

        sortArray(array, arraySize);

        write(pipe_fd[1], &arraySize, sizeof(arraySize));
        write(pipe_fd[1], array, arraySize*sizeof(array));

        close(pipe_fd[1]);
    }else 
    {
        int status;
        wait(&status);

        read(pipe_fd[0], &arraySize, sizeof(arraySize));
        read(pipe_fd[0], array, arraySize*sizeof(array));

        close(pipe_fd[0]);

        printf("Sorted Array : ");
        printArray(array, arraySize);
    }

    free(array);

    return 0;
}