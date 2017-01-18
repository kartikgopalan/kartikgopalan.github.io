#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    pid_t pid;

    if (argc == 1)
    {
        printf("Usage: %s command [arguments]\n", argv[0]);
        return 1;
    }

    //Create a child process
    pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "Fork failed: %s\n", strerror(errno));
        return 1;
    }

    if (pid == 0)
    {
        //Child executes the command
        // ./process ls -al
        // argv = ["./process", "ls", "-al", NULL]
        // argv[1] = "ls"
        // argv+1 = ["ls", "-al", NULL]
        execvp(argv[1], argv+1);

        //If we get here execvp failed
        fprintf(stderr, "Failed to execute: %s\n", strerror(errno));
        return 1;
    }

    //Parent waits for child
    if (waitpid(pid, NULL, 0) == -1 && errno != ECHILD)
    {
        fprintf(stderr, "Wait failed: %s\n", strerror(errno));
        return 1;
    }

    return 0;
}
