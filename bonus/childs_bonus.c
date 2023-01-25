#include "../bonus_includes/pipex_bonus.h"

static char *get_path(char *command, char **paths)
{
    char *tmp;
    char *cmd;

    while(*paths)
    {
        tmp = ft_strjoin(*paths, "/");
        cmd = ft_strjoin(tmp, command);
        if (access(cmd, 0) == 0)
           return (cmd);
        free(cmd);
        paths ++;
    }
    return (NULL);
}

static void	change_std(int zero, int first)
{
	dup2(zero, 0);
	dup2(first, 1);
}

void    child(char **argv, char *envp[], t_pipe *pipex)
{
    pipex->pid = fork();
    if (pipex->pid == 0)
    {
        if (pipex->pipe_pos == 0)
            change_std(pipex->infile, pipex->pipe[1]);
        else if (pipex->pipe_pos == pipex->nb_cmd - 1)
            change_std(pipex->pipe[2 * pipex->pipe_pos - 2], pipex->outfile);
        else
            change_std(pipex->pipe[2 * pipex->pipe_pos - 2], pipex->pipe[2 * pipex->pipe_pos + 1]);
    close_pipes(pipex);
    pipex->arg = ft_split(argv[2 + pipex->here_doc + pipex->pipe_pos], ' ');
    pipex->cmd = get_path(pipex->arg[0], pipex->paths);
    if (!pipex->cmd)
    {
        free_child(pipex);
        w_msg(ERR_CMD);
        exit(1);
    }
    execve(pipex->cmd, pipex->arg, envp);
    }
}