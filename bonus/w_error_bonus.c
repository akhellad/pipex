#include "../bonus_includes/pipex_bonus.h"

int	w_msg(char *err_msg)
{
	write(2, err_msg, ft_strlen(err_msg));
	return (1);
}

void	w_error_msg(char *err_msg)
{
	perror(err_msg);
	exit (1);
}