#include "../includes/pipex.h"

void    free_parent(t_pipe *pipex)
{
    int i;

    i = 0;
    close(pipex->infile);
    close(pipex->outfile);
    while (pipex->paths[i])
    {
        free(pipex->paths[i]);
        i ++;
    }
    free(pipex->paths);
    free(pipex->pipe);
}


void    free_child(t_pipe *pipex)
{
    int i;

    i = 0;
    while (pipex->arg[i])
    {
        free (pipex->arg[i]);
        i ++;
    }
    free (pipex->cmd);
    free (pipex->arg);
}

void	pipe_free(t_pipe *pipex)
{
	close(pipex->infile);
	close(pipex->outfile);
	free(pipex->pipe);
	exit(1);
}