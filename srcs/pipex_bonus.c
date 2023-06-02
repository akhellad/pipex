/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:20:09 by akhellad          #+#    #+#             */
/*   Updated: 2023/06/02 15:27:35 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process(int pipe_fd[2], char argv[], char **envp)
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

void	pipe_process(int i, int argc, char **argv, char **envp)
{
	int	pipe_fd[2];
	int	fileout;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	fileout = open_file(argv[argc - 1], 1);
	dup2(fileout, STDOUT_FILENO);
	while (i < argc - 2)
	{
		child_process(pipe_fd, argv[i], envp);
		i++;
	}
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	execute(argv[argc - 2], envp);
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
	usage();
}
