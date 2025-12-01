/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mewen <mewen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 10:00:00 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/01 23:18:16 by mewen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

static void	child_fonction(char **argv, char *env[], int fd, int pipefd[2])
{
	dup2(fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(fd);
	close(pipefd[0]);
	close(pipefd[1]);
	execve(argv[0], argv, env);
	perror("execve");
	exit(EXIT_FAILURE);
}

int	creat_process(char **argv, char *env[], int fd)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child_fonction(argv, env, fd, pipefd);
	close(pipefd[1]);
	close(fd);
	waitpid(pid, NULL, 0);
	return (pipefd[0]);
}
