#include "../bonus_includes/pipex_bonus.h"

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] == s2[i])
			i ++;
		else
			return (1);
	}
	return (0);
}

static void create_pipes(t_pipe *pipex)
{
    int i;

    i = 0;
    while (i < pipex->nb_cmd - 1)
    {
        if (pipe(pipex->pipe + 2 * i) < 0)
            free_parent(pipex);
        i ++;
    }
}

void	close_pipes(t_pipe *pipex)
{
	int	i;

	i = 0;
	while (i < (pipex->nb_pipe))
	{
		close(pipex->pipe[i]);
		i++;
	}
}

char *find_path_line(char *envp[])
{
    while (ft_strncmp("PATH", *envp, 4))
        envp ++;
    return (*envp + 5); 
}

void open_files(int argc, char **argv, t_pipe *p)
{
    if (p->here_doc)
    {
        here_doc(argv[2], p);
        p->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0000644);
    }
    else
    {
        p->infile = open(argv[1], O_RDONLY, 0777);
        if (p->infile < 0)
            w_error_msg(ERR_INFILE);
        p->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0000644);
        if (p->outfile < 0)
            w_error_msg(ERR_OUTFILE);
    }
}

int main(int argc, char *argv[], char *envp[])
{
    t_pipe pipex;
    if (argc < check_here_doc(argv[1], &pipex))
        return(w_msg(ERR_INPUT));
    open_files(argc, argv, &pipex);
    pipex.nb_cmd = argc - 3 - pipex.here_doc;
    pipex.nb_pipe = 2 * (pipex.nb_cmd - 1);
    pipex.pipe = malloc(sizeof(int) * pipex.nb_pipe);
    if (!pipex.pipe)
        w_error_msg(ERR_PIPE);
    pipex.path_line = find_path_line(envp);
    pipex.paths = ft_split(pipex.path_line, ':');
    if (!pipex.paths)
        pipe_free(&pipex);
    create_pipes(&pipex);
    pipex.pipe_pos = -1;
    while(++(pipex.pipe_pos) < pipex.nb_cmd)
        child(argv, envp, &pipex);
    close_pipes(&pipex);
    waitpid(-1, NULL, 0);
    free_parent(&pipex);
    return (0);
}