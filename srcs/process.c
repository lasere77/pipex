/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:08:24 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/11 17:30:47 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

void	panic_free(t_cmd *cmd, char *str)
{
	if (str)
		perror(str);
	close_cmd_fds(cmd);
	unset_cmd(cmd);
	exit(EXIT_FAILURE);
}

void	do_dup2(t_cmd *cmd, int i)
{
	if (cmd[i].infile)
		cmd[i].fd_in = open(cmd[i].infile, O_RDONLY);
	if (cmd[i].outfile)
	{
		if (access(cmd[i].outfile, F_OK | W_OK) == 0)
			unlink(cmd[i].outfile);
		cmd[i].fd_out = open(cmd[i].outfile,
				O_RDONLY | O_WRONLY | O_CREAT, 0644);
	}
	if (dup2(cmd[i].fd_in, STDIN_FILENO) == -1)
		panic_free(cmd, "dup2");
	if (dup2(cmd[i].fd_out, STDOUT_FILENO) == -1)
		panic_free(cmd, "dup2");
	if (cmd[i].fd_in >= 0)
		close(cmd[i].fd_in);
	if (cmd[i].fd_out >= 0)
		close(cmd[i].fd_out);
	if (cmd[i + 1].valid && cmd[i + 1].fd_in >= 0)
		close(cmd[i + 1].fd_in);
}

void	do_child(t_cmd *cmd, int i, char **env)
{
	char	**path;
	char	*bin_path;
	pid_t	pid;

	pid = fork();
	cmd[i].pid = pid;
	if (pid == -1)
		panic_free(cmd, "fork");
	if (pid == 0)
	{
		do_dup2(cmd, i);
		path = get_path(env);
		bin_path = get_bin_path(path, cmd[i].argv[0]);
		free_split(path);
		if (!bin_path)
		{
			if (access(cmd[i].argv[0], F_OK | X_OK) != 0)
				panic_free(cmd, cmd[i].argv[0]);
			bin_path = cmd[i].argv[0];
		}
		execve(bin_path, cmd[i].argv, env);
		free(bin_path);
		panic_free(cmd, "execve");
	}
}

int	pipex(t_cmd *cmd, char **env)
{
	int	pipefd[2];
	int	i;

	i = 0;
	while (cmd[i].valid)
	{
		if (!cmd[i].outfile)
		{
			if (pipe(pipefd) == -1)
				panic_free(cmd, "pipe");
			cmd[i].fd_out = pipefd[1];
			cmd[i + 1].fd_in = pipefd[0];
		}
		do_child(cmd, i, env);
		if (cmd[i].fd_in >= 0)
			close(cmd[i].fd_in);
		if (cmd[i].fd_out >= 0)
			close(cmd[i].fd_out);
		i++;
	}
	return (get_status(cmd));
}

int	get_status(t_cmd *cmd)
{
	int	status;
	int	i;

	i = 0;
	while (cmd[i].valid)
	{
		waitpid(cmd[i].pid, &status, 0);
		if (WIFEXITED(status))
			WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			WTERMSIG(status);
		else if (WIFSTOPPED(status))
			WSTOPSIG(status);
		i++;
	}
	return (WIFEXITED(status));
}
