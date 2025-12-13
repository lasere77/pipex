/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:37:49 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/13 12:09:01 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process_utils_bonus.h"

int	get_status(t_cmd *cmd)
{
	int	status;
	int	result;
	int	i;

	i = 0;
	result = 0;
	while (cmd[i].valid)
	{
		waitpid(cmd[i].pid, &status, 0);
		if (WIFEXITED(status))
			result = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			result = WTERMSIG(status);
		else if (WIFSTOPPED(status))
			result = WSTOPSIG(status);
		i++;
	}
	return (result);
}

void	panic_free(t_cmd *cmd, char *str, int exit_code)
{
	if (str)
		perror(str);
	close_cmd_fds(cmd);
	unset_cmd(cmd);
	exit(exit_code);
}

char	*get_command(t_cmd *cmd, int i, char **env)
{
	char	**path;
	char	*bin_path;

	path = get_path(env);
	bin_path = get_bin_path(path, cmd[i].argv[0]);
	free_split(path);
	if (!bin_path)
	{
		if (!cmd[i].argv[0] || !*(cmd[i].argv[0])
			|| access(cmd[i].argv[0], F_OK | X_OK) != 0)
		{
			if (!cmd[i].argv[0] || !ft_strchr(cmd[i].argv[0], '/'))
				ft_printfd(2, "%s: command not found\n", cmd[i].argv[0]);
			else
				panic_free(cmd, cmd[i].argv[0], 127);
			panic_free(cmd, NULL, 127);
		}
		bin_path = ft_strdup(cmd[i].argv[0]);
	}
	if (access(bin_path, F_OK | X_OK) != 0)
	{
		free(bin_path);
		panic_free(cmd, cmd[i].argv[0], 127);
	}
	return (bin_path);
}

char	do_dup2(t_cmd *cmd, int i)
{
	if (dup2(cmd[i].fd_in, STDIN_FILENO) == -1)
		return (1);
	if (dup2(cmd[i].fd_out, STDOUT_FILENO) == -1)
		return (1);
	if (cmd[i].fd_in >= 0)
		close(cmd[i].fd_in);
	if (cmd[i].fd_out >= 0)
		close(cmd[i].fd_out);
	if (cmd[i + 1].valid && cmd[i + 1].fd_in >= 0)
		close(cmd[i + 1].fd_in);
	return (0);
}
