#include "../includes/pipex.h"

void    init_struct(int argc, char **argv, t_pipe *pipex)
{
    pipex->child1.file = open(argv[1], O_RDONLY | O_CREAT, 0777);
    pipex->child2.file = open(argv[argc - 1], O_WRONLY | O_CREAT, 0777);
    pipex->child1.arg = ft_split(argv[2], ' ');
    pipex->child1.arg[0] = ft_strjoin("/usr/bin/", pipex->child1.arg[0]);
    pipex->child1.path = ft_strdup(pipex->child1.arg[0]);
    pipex->child2.arg = ft_split(argv[3], ' ');
    pipex->child2.arg[0] = ft_strjoin("/usr/bin/", pipex->child2.arg[0]);
    pipex->child2.path = ft_strdup(pipex->child2.arg[0]);
}

int main(int argc, char* argv[]) {
    t_pipe pipex;
    init_struct(argc, argv, &pipex);
    if (pipe(pipex.fd) == -1) 
        return 1;    
    pipex.pid1 = fork();
    if (pipex.pid1 < 0)
        return 2;   
    if (pipex.pid1 == 0) {
        dup2(pipex.fd[1], STDOUT_FILENO);
        close(pipex.fd[0]);
        dup2(pipex.child1.file, STDIN_FILENO);
        execve(pipex.child1.path, pipex.child1.arg, NULL);
    }
    
    int pid2 = fork();
    if (pid2 < 0)
        return 3;
    if (pid2 == 0) {
        dup2(pipex.fd[0], STDIN_FILENO);
        close(pipex.fd[1]);
        dup2(pipex.child2.file, STDOUT_FILENO);
        execve(pipex.child2.path, pipex.child2.arg, NULL);
    }
    
    close(pipex.fd[0]);
    close(pipex.fd[1]);
    
    waitpid(pipex.pid1, NULL, 0);
    waitpid(pipex.pid2, NULL, 0);
    
    return 0;
}