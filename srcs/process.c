/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:08:24 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/12 10:48:48 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "process_utils.h"

void	get_infile_outfile(t_cmd *cmd, int i)
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
}

void	do_child(t_cmd *cmd, int i, char **env)
{
	char	*bin_path;
	pid_t	pid;

	pid = fork();
	cmd[i].pid = pid;
	if (pid == -1)
		panic_free(cmd, "fork", EXIT_FAILURE);
	if (pid == 0)
	{
		get_infile_outfile(cmd, i);
		bin_path = get_command(cmd, i, env);
		do_dup2(cmd, i);
		execve(bin_path, cmd[i].argv, env);
		free(bin_path);
		panic_free(cmd, "execve", EXIT_FAILURE);
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
				panic_free(cmd, "pipe", EXIT_FAILURE);
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
