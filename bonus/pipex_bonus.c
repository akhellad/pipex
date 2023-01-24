#include "../bonus_includes/pipex_bonus.h"

void check_leaks();

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

char *find_path_line(char *envp[])
{
    while (ft_strncmp("PATH", *envp, 4))
        envp ++;
    return (*envp + 5); 
}

void open_files(int argc, char **argv, t_pipe *p)
{
    if (p->here_doc)
        here_doc(argv[2], p);
    else
        p->child1.file = open(argv[1], O_RDONLY, 0777);
    if (p->child1.file < 0)
        w_error_msg(ERR_INFILE);
    p->child2.file = open(argv[argc - 1], O_WRONLY | O_CREAT, 0777);
    if (p->child2.file < 0)
        w_error_msg(ERR_OUTFILE);
}

int main(int argc, char *argv[], char *envp[])
{
    t_pipe pipex;
    if (argc < check_here_doc(argv[1], &pipex))
        return(w_msg(ERR_INPUT));
    open_files(argc, argv, &pipex);
    pipex.path_line = find_path_line(envp);
    pipex.paths = ft_split(pipex.path_line, ':');
    if (pipe(pipex.fd) < 0) 
        w_error_msg(ERR_PIPE);    
    pipex.pid1 = fork(); 
    if (pipex.pid1 == 0) 
        first_child(argc, argv, envp, &pipex);    
    pipex.pid2 = fork();
    if (pipex.pid2 == 0)
        second_child(argc, argv, envp, &pipex);
    close(pipex.fd[0]);
    close(pipex.fd[1]);   
    waitpid(pipex.pid1, NULL, 0);
    waitpid(pipex.pid2, NULL, 0);
    free_parent(&pipex);
    check_leaks();
    return (0);
}