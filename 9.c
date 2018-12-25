#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc,char** argv)
{
    printf("Parrent before\n");
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("Parrent after (error)");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        if(execvp("cat", argv) == -1)
        {
            perror("Child in process (error)");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        printf("Parrent in process\n");
        int status;
        if (waitpid(pid, &status,0) == -1)
        {
            perror("Parrent in process (error)");
            exit(EXIT_FAILURE);
        }

        printf("Parrent after\n");
        exit(EXIT_FAILURE);
    }
}
