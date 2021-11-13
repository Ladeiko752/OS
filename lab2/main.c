#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

void generating_random_numbers(int arr[5]){
    srand(time(NULL));
    for (int i = 0; i < 5; ++i) {
        arr[i] = rand();
    }
}

void read_buffer(int arr[5]){
    for (int i = 0; i < 5; ++i) {
        printf("%d\n", arr[i]);
    }
}

void write_numbers_in_file(int arr[5]){
    FILE * file = NULL;
    file = fopen("aboba.txt", "w");
    if (file == NULL) {
        printf("Error");
        getchar();
        abort();
    }
    for (int i = 0; i < 5; ++i){
        fprintf(file, "%d\n", arr[i]);
    }
    fclose(file);
}

int main() {
    pid_t p1, p2;
    int buffer[5];
    printf("Start program\n");
    printf("Root with PID:%d\n", getpid());
    generating_random_numbers(buffer);
    p1 = fork();
    if(p1 < 0){
        perror("Warning");
        abort();
    }else if (p1 == 0){
        printf("P1 PID: %d and PPID: %d\n", getpid(), getppid());
        read_buffer(buffer);
    } else{
        p2 = fork();
        if(p2 < 0){
            perror("Warning");
            abort();
        }else if(p2 == 0){
            printf("P2 PID: %d and PPID: %d\n", getpid(), getppid());
            write_numbers_in_file(buffer);
        }
    }
    wait((int *) p2);
    wait((int *) p1);


    return 0;
}
