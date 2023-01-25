#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include "get_next_line.h"

# define ERR_INFILE "Infile"
# define ERR_OUTFILE "Outfile"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe"
# define ERR_CMD "Command not found\n"
# define ERR_HEREDOC "here_doc"

typedef struct s_pipe
{
    pid_t   pid;
    int     infile;
    int     outfile;
    char    **arg;
    char    *path_line;
    char    **paths;
    char    *cmd;
    int     nb_cmd;
    int     here_doc;
    int     nb_pipe;
    int     *pipe;
    int     pipe_pos;
} t_pipe;

char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *src);
int	    ft_strcmp(char *s1, char *s2);
size_t	ft_strlen(const char *str);
void    child(char **argv, char *envp[], t_pipe *pipex);
int     w_msg(char *err_msg);
void	w_error_msg(char *err_msg);
void    free_child(t_pipe *pipex);
int     ft_strncmp(char *s1, char *s2, unsigned int n);
char    *find_path_line(char *envp[]);
void    free_parent(t_pipe *pipex);
void	here_doc(char *av, t_pipe *pipex);
int 	check_here_doc(char *av, t_pipe *pipex);
void	close_pipes(t_pipe *pipex);
void	pipe_free(t_pipe *pipex);

#endif