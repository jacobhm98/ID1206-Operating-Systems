#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid = fork();
    printf ("pid = %d\n", pid);
    if (pid == 0){
        printf("im the child, %d\n", getpid());
        sleep(1);
        return 42;
    }
    else {
        int res;
        printf("my child is %d\n", pid);
        wait(&res);
        printf("the result was %d\n", WEXITSTATUS(res));
    }
    printf("thats it %d\n", getpid());
    return 0;
}
