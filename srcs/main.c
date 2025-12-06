/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:35:56 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/06 20:19:18 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "utils.h"
#include "arg.h"

#include <sys/wait.h>

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

static int	do_child(t_cmd *cmd, int index_cmd, int fd, pid_t *list_pid)
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

static void	wait_child(t_cmd *cmd, pid_t *list_pid)
{
	size_t	i;

	i = 0;
	while (i < get_nb_cmd(cmd))
	{
		waitpid(list_pid[i], &cmd[i].status, 0);
		i++;
	}
}

static int	exec_cmd(t_cmd *cmd, int fd)
{
	pid_t	*list_pid;
	size_t	i;

	list_pid = malloc(sizeof(pid_t) * (get_nb_cmd(cmd) + 1));
	if (!list_pid)
		return (-1);
	i = 0;
	while (i < get_nb_cmd(cmd))
	{
		fd = do_child(cmd, i, fd, &list_pid[i]);
		i++;
	}
	wait_child(cmd, list_pid);
	free(list_pid);
	return (fd);
}

int	main(int argc, char *argv[], char *env[])
{
	t_cmd	*cmd;
	int		fd;
	int		status;

	cmd = set_cmd(argc, argv, env);
	if (!cmd)
		return (1);
	fd = open_input_file(argv[1]);
	fd = exec_cmd(cmd, fd);
	status = cmd[get_nb_cmd(cmd) - 1].status;
	unset_cmd(cmd);
	write_in_file(argv[argc - 1], fd);
	if (fd >= 0)
		close(fd);
	if (!is_last_cmd_valid(argc, argv, env))
		return (127);
	return (WEXITSTATUS(status));
}
