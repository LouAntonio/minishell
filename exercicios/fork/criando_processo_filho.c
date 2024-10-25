#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int main(void)
{
    pid_t   x;
    x = fork();
    if (x == 0)
    {
        printf("PID filho: %d\n", (int)getpid());
        printf("Sou o processo filho, %d\n", x);
    }
    else
    {
        printf("PID pai: %d\n", (int)getpid());
        printf("Sou o processo pai, meu filho tem o PID = %d\n", x);
        printf("--------------------------------------\n");
        exit(0);
    }
}