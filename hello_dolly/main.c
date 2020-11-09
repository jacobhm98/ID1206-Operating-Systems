#include "hello_dolly.h"

int entry_point();
int clone();
int parents();
int groupd_n_dat();


int main() {
    parents();
    return 0;
}

int clone() {
    int pid;
    int x = 123;
    pid = fork();

    if (pid == 0) {
        printf("child x is %d\n", x);
        x = 42;
        sleep(1);
        printf("child x is %d\n", x);
    } else {
        printf("mother x is %d\n", x);
        x = 13;
        sleep(1);
        printf("mother x is %d\n", x);
        wait(NULL);
    }
    return 0;
}

int parents(){
    int pid = fork();
    if (pid == 0){
        printf("im the child %d with parent process %d\n", getpid(), getppid());
    }
    else {
        printf("im the parent %d with parent process %d\n", getpid(), getppid());
        wait(NULL);
    }
    return 0;
}