#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>

# define ERR_INFILE "Infile"
# define ERR_OUTFILE "Outfile"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe"
# define ERR_CMD "Command not found\n"

typedef struct s_child
{
    char    *path;
    char    **arg;
    int     file;
} t_child;

typedef struct s_pipe
{
    pid_t   pid1;
    pid_t   pid2;
    int     fd[2];
    t_child child1;
    t_child child2;
} t_pipe;

char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *src);
int	    ft_strcmp(char *s1, char *s2);
size_t	ft_strlen(const char *str);

#endif