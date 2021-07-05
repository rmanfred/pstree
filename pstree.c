#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void ft_wait(pid_t pid)
{
    int status = 0;
    if ((waitpid(-1, &status, WUNTRACED)) == -1)
        write(-1, "Waitpid error\n", strlen("Waitpid error\n"));
    WEXITSTATUS(status);
}

void ft_execute()
{
    pid_t pid;
    int exec;

    pid = fork();
    if (!pid)
    {
        exec = execlp("pstree", "pstree", (int *)NULL);
        if (exec < 0)
        {
            write(2, "command not found\n", strlen("command not found\n"));
            exit(127);
        }
    }
    else if (pid < 0)
    {
        write(2, "fork error\n", strlen("fork error\n"));
        exit(127);
    }
    else
        ft_wait(pid);
}

int main()
{
   ft_execute();
}
