#include "../includes/pipex.h"

void    free_child1(t_pipe *pipex)
{
    int i;

    i = 0;
    close(pipex->child1.file);
    while (pipex->child1.arg[i])
    {
        free(pipex->child1.arg[i]);
        i ++;
    }
    free(pipex->child1.arg);
}

void    free_child2(t_pipe *pipex)
{
    int i;

    i = 0;
    close(pipex->child2.file);
    while (pipex->child2.arg[i])
    {
        free(pipex->child2.arg[i]);
        i ++;
    }
    free(pipex->child2.arg);
}

void    free_parent(t_pipe *pipex)
{
    int i;

    i = 0;
    free (pipex->cmd);
//    free (pipex->path_line);
    while (pipex->paths[i])
    {
        free (pipex->paths[i]);
        i ++;
    }
    free (pipex->paths);
}