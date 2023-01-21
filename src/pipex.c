#include "../includes/pipex.h"

void open_files(int argc, char **argv, t_pipe *p)
{
    p->child1.file = open(argv[1], O_RDONLY, 0777);
    if (p->child1.file < 0)
        w_error_msg(ERR_INFILE);
    p->child2.file = open(argv[argc - 1], O_WRONLY, 0777);
    if (p->child2.file < 0)
        w_error_msg(ERR_OUTFILE);
}

void    init_struct(int argc, char **argv, t_pipe *p)
{
    open_files(argc, argv, p);
    p->child1.arg = ft_split(argv[2], ' ');
    p->child1.arg[0] = ft_strjoin(PATH, p->child1.arg[0]);
    p->child1.path = ft_strdup(p->child1.arg[0]);
    p->child2.arg = ft_split(argv[3], ' ');
    p->child2.arg[0] = ft_strjoin(PATH, p->child2.arg[0]);
    p->child2.path = ft_strdup(p->child2.arg[0]);
}

int main(int argc, char* argv[])
{
    t_pipe pipex;
    if (argc != 5)
        return(w_msg(ERR_INPUT)); 
    init_struct(argc, argv, &pipex);
    if (pipe(pipex.fd) < 0) 
        w_error_msg(ERR_PIPE);    
    pipex.pid1 = fork(); 
    if (pipex.pid1 == 0) 
        first_child(&pipex);    
    pipex.pid2 = fork();
    if (pipex.pid2 == 0)
        second_child(&pipex);
    close(pipex.fd[0]);
    close(pipex.fd[1]);   
    waitpid(pipex.pid1, NULL, 0);
    waitpid(pipex.pid2, NULL, 0);
    free_child(&pipex);
    return (0);
}