/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 11:13:20 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/07 11:37:52 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

static void	child_fonction(t_cmd cmd, int fd, int pipefd[2])
{
	if (fd >= 0)
	{
		dup2(fd, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(fd);
		close(pipefd[0]);
		close(pipefd[1]);
		execve(cmd.arg[0], cmd.arg, cmd.env);
		perror("execve");
	}
	close(pipefd[0]);
	close(pipefd[1]);
}

int	do_child(t_cmd *cmd, int index_cmd, int fd, pid_t *list_pid)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		panic_free(cmd, list_pid);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		panic_free(cmd, list_pid);
	}
	if (pid == 0)
	{
		child_fonction(cmd[index_cmd], fd, pipefd);
		panic_free(cmd, list_pid);
	}
	close(pipefd[1]);
	if (fd > 2)
		close(fd);
	list_pid[0] = pid;
	return (pipefd[0]);
}

void	wait_child(t_cmd *cmd, pid_t *list_pid)
{
	size_t	i;

	i = 0;
	while (i < get_nb_cmd(cmd))
	{
		waitpid(list_pid[i], &cmd[i].status, 0);
		i++;
	}
}
