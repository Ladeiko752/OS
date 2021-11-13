#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2, pid3, pid4, pid5, pid6;
    printf("START PROGRAM\n");
    printf("Root with PID: %d\n\n", getpid());
    pid1 = fork();
//    wait(NULL);
    if(pid1 < 0){
        printf("PROCESS CREATION ERROR!\n");
        abort();
    } else if(pid1 == 0){
        printf("Child-process #2 with PID: %d and PPID: %d\n", getpid(), getppid());
        pid3 = fork();
        wait(NULL);
        if(pid3 < 0){
            printf("PROCESS CREATION ERROR!\n");
            abort();
        } else if(pid3 == 0){
            printf("Child-process #4 with PID: %d and PPID: %d\n", getpid(), getppid());
            pid4 = fork();
            wait(NULL);
            if(pid4 < 0){
                printf("PROCESS CREATION ERROR!\n");
                abort();
            } else if (pid4 == 0){
                printf("Child-process #6 with PID: %d and PPID: %d\n", getpid(), getppid());
                pid6 = fork();
                wait(NULL);
                if(pid6 < 0){
                    printf("PROCESS CREATION ERROR!\n");
                    abort();
                } else if(pid6 == 0){
                    printf("Child-process #7 with PID: %d and PPID: %d\n", getpid(), getppid());
                    printf("Child-process #7 terminated\n");
                    exit(0);
                }
                printf("Child-process #6 terminated\n");
                exit(0);
            } else{
                pid5 = fork();
                if(pid5 < 0){
                    printf("PROCESS CREATION ERROR!\n");
                    abort();
                } else if(pid5 == 0){
                    printf("Child-process #5 with PID: %d and PPID: %d\n", getpid(), getppid());
                    printf("Child-process #5 terminated\n");
                    exit(0);
                }
                execl("/bin/pwd", "pwd", NULL);
            }
        }
        printf("Child-process #2 terminated\n");
        exit(0);
    } else{
        pid2 = fork();
        if(pid2 < 0){
            printf("PROCESS CREATION ERROR!\n");
            abort();
        } else if(pid2 == 0){
            printf("Child-process #3 with PID: %d and PPID: %d\n", getpid(), getppid());
            printf("Child-process #3 terminated\n");
            exit(0);
        }
    }
    wait((int *) pid2);
    wait((int *) pid1);

    return 0;
}
