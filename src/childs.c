#include "../includes/pipex.h"

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

void    first_child(int argc, char **argv, char *envp[], t_pipe *pipex)
{
    (void)argc;
    dup2(pipex->fd[1], STDOUT_FILENO);
    close(pipex->fd[0]);
    dup2(pipex->child1.file, STDIN_FILENO);
    pipex->child1.arg = ft_split(argv[2], ' ');
    pipex->cmd = get_path(pipex->child1.arg[0], pipex->paths);
    if (!pipex->cmd)
    {
        free_child1(pipex);
        w_msg(ERR_CMD);
        exit(1);
    }
    execve(pipex->cmd, pipex->child1.arg, envp);
}

void    second_child(int argc, char **argv, char *envp[], t_pipe *pipex)
{
    (void)argc;
    dup2(pipex->fd[0], STDIN_FILENO);
    close(pipex->fd[1]);
    dup2(pipex->child2.file, STDOUT_FILENO);
    pipex->child2.arg = ft_split(argv[3], ' ');
    pipex->cmd = get_path(pipex->child2.arg[0], pipex->paths);
    if (!pipex->cmd)
    {
        free_child2(pipex);
        w_msg(ERR_CMD);
        exit(1);
    }
    execve(pipex->cmd, pipex->child2.arg, envp);
}