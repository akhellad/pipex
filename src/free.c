#include "../includes/pipex.h"

void    free_child(t_pipe *pipex)
{
    int i;

    i = 0;
    close(pipex->child1.file);
    close(pipex->child2.file);
    free(pipex->child1.path);
    free(pipex->child2.path);
    while (pipex->child1.arg[i])
    {
        free(pipex->child1.arg[i]);
        i ++;
    }
    free(pipex->child1.arg);
    i = 0;
    while (pipex->child2.arg[i])
    {
        free(pipex->child2.arg[i]);
        i ++;
    }
    free(pipex->child2.arg);
}
