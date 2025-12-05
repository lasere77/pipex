/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 10:00:00 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/05 17:59:44 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "arg.h"

static void	child_error_free(pid_t *tab_pid, char **path)
{
	free(tab_pid);
	free_split(path);
	exit(EXIT_FAILURE);
}

static void	child_fonction(char **argv, char *env[], int fd, int pipefd[2])
{
	if (fd >= 0)
	{
		dup2(fd, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(fd);
		close(pipefd[0]);
		close(pipefd[1]);
		execve(argv[0], argv, env);
		perror("execve");
	}
	close(pipefd[0]);
	close(pipefd[1]);
	free_split(argv);
}

int	creat_process(char **argv, char *env[], int fd, pid_t *tab_pid, char **path)
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
	{
		child_fonction(argv, env, fd, pipefd);
		child_error_free(tab_pid, path);
	}
	close(pipefd[1]);
	if (fd > 2)
		close(fd);
	tab_pid[0] = pid;
	return (pipefd[0]);
}
