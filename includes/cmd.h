/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 13:24:05 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/07 12:10:31 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include <stddef.h>

typedef struct s_cmd
{
	char	**arg;
	char	**env;
	int		status;
}			t_cmd;

t_cmd	*set_cmd(int argc, char **argv, char **env);
void	unset_cmd(t_cmd	*cmd);
size_t	get_nb_cmd(t_cmd *cmd);

#endif