#include "../bonus_includes/pipex_bonus.h"

int		check_here_doc(char *av, t_pipe *pipex)
{
	if (!ft_strcmp(av, "here_doc"))
	{
		pipex->here_doc = 1;
		return (6);
	}
	else
	{
		pipex->here_doc = 0;
		return (5);
	}
}

void	here_doc(char *av, t_pipe *pipex)
{
	int tmp_file;
	char *buff;

	tmp_file = 0;
	if (pipex->here_doc)
		tmp_file = open(".here_doc", O_CREAT | O_WRONLY , 0777);
	if (tmp_file < 0)
		w_error_msg(ERR_HEREDOC);
	while (1)
	{
		write(1, "pipe heredoc>", 13);
		buff = get_next_line(0);
		write(tmp_file, buff, ft_strlen(buff));
		write(tmp_file, "\n", 2);
		if (ft_strcmp(av, buff))
			break ;
		free(buff);
	}
	free(buff);
	close(tmp_file);
	pipex->child1.file = open(".here_doc", O_RDONLY, 0777);
	if (pipex->child1.file < 0)
		w_error_msg(ERR_HEREDOC);
}