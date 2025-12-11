/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:21:03 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/11 15:17:58 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

t_cmd	*set_cmd(int nb_cmd, char **argv)
{
	t_cmd	*cmd;
	size_t	i;

	cmd = malloc(sizeof(t_cmd) * (nb_cmd + 1));
	if (!cmd)
		return (NULL);
	i = 0;
	while (i < (size_t)nb_cmd)
	{
		cmd[i].valid = 1;
		cmd[i].infile = NULL;
		if (i == 0)
			cmd[i].infile = argv[1];
		cmd[i].outfile = NULL;
		if (i == (size_t)nb_cmd - 1)
			cmd[i].outfile = argv[nb_cmd + 2];
		cmd[i].argv = ft_split(argv[2 + i], ' ');
		cmd[i].fd_in = -1;
		cmd[i].fd_out = -1;
		i++;
	}
	cmd[nb_cmd].valid = 0;
	return (cmd);
}

void	close_cmd_fds(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i].valid)
	{
		if (cmd[i].fd_in >= 0)
			close(cmd[i].fd_in);
		if (cmd[i].fd_out >= 0)
			close(cmd[i].fd_out);
		i++;
	}
}

void	unset_cmd(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i].valid)
	{
		free_split(cmd[i].argv);
		i++;
	}
	free(cmd);
}
