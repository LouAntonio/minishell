#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    pid_t pid_filho;

    pid_filho = fork();
    if (pid_filho > 0)
        sleep(60);
    else
        exit(0);
    return (0);
}