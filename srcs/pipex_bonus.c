/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:20:09 by akhellad          #+#    #+#             */
/*   Updated: 2023/06/05 16:33:04 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

pid_t	child_process(int pipe_fd[2], char argv[], char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		execute(argv, envp);
		exit(0);
	}
	return (pid);
}

void	here_doc(char *limiter, int argc)
{
	pid_t	reader;
	int		fd[2];
	char	*line;

	if (argc < 6)
		usage();
	if (pipe(fd) == -1)
		error();
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		while (get_next_line(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

void	wait_process(int pipe_fd[2], pid_t *child_pids, int child_count)
{
	int	j;

	j = 0;
	while (j < child_count)
	{
		waitpid(child_pids[j], NULL, 0);
		j++;
	}
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	free(child_pids);
}

void	pipe_process(int i, int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	int		fileout;
	int		child_count;
	pid_t	*child_pids;
	int		j;

	child_count = argc - i - 2;
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	fileout = open_file(argv[argc - 1], 1);
	child_pids = malloc(child_count * sizeof(pid_t));
	j = 0;
	while (j < child_count)
	{
		child_pids[j] = child_process(pipe_fd, argv[i], envp);
		i++;
		j++;
	}
	close(pipe_fd[0]);
	dup2(fileout, STDOUT_FILENO);
	close(fileout);
	wait_process(pipe_fd, child_pids, child_count);
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	filein;

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			here_doc(argv[2], argc);
			i = 3;
		}
		else
		{
			filein = open_file(argv[1], 2);
			dup2(filein, STDIN_FILENO);
			i = 2;
		}
		pipe_process(i, argc, argv, envp);
	}
	else
		usage();
}
