/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:15:05 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/12 14:43:27 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "arg_bonus.h"

typedef struct s_cmd
{
	char	*infile;
	char	*outfile;
	char	**argv;
	int		fd_in;
	int		fd_out;
	int		pid;
	char	valid;
}			t_cmd;

t_cmd	*set_cmd(int nb_cmd, char **argv);
void	close_cmd_fds(t_cmd *cmd);
void	unset_cmd(t_cmd *cmd);

#endif