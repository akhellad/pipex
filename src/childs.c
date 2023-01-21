#include "pipex.h"

void    first_child(t_pipe *pipex)
{
    dup2(pipex->fd[1], STDOUT_FILENO);
    close(pipex->fd[0]);
    dup2(pipex->child1.file, STDIN_FILENO);
    execve(pipex->child1.path, pipex->child1.arg, NULL);
}

void    second_child(t_pipe *pipex)
{
    dup2(pipex->fd[0], STDIN_FILENO);
    close(pipex->fd[1]);
    dup2(pipex->child2.file, STDOUT_FILENO);
    execve(pipex->child2.path, pipex->child2.arg, NULL);
}