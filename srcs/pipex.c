/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:20:05 by akhellad          #+#    #+#             */
/*   Updated: 2023/06/05 16:17:37 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process(char **argv, char **envp, int *fd)
{
	int		filein;

	filein = open(argv[1], O_RDONLY, 0777);
	if (filein == -1)
	{
		perror("Error opening input file");
		close(fd[0]);
		close(fd[1]);
		exit (1);
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(filein);
	execute(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int		fileout;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
	{
		perror("Error opening output file");
		close(fd[0]);
		close(fd[1]);
		exit(1);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
	close(fileout);
	execute(argv[3], envp);
}

void	fork_process(char **argv, char **envp, int fd[2])
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid1 == 0)
		child_process(argv, envp, fd);
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		exit (1);
	}
	if (pid2 == 0)
		parent_process(argv, envp, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];

	if (argc == 5)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			exit(1);
		}
		fork_process(argv, envp, fd);
		close(0);
		close(1);
		close(2);
	}
	else
		ft_putstr_fd("Bad arguments. Ex: ./pipex file1 cmd1 cmd2 file2\n", 1);
	return (0);
}
