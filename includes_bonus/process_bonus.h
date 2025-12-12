/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:08:53 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/12 15:01:37 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include "cmd_bonus.h"

void	do_child(t_cmd *cmd, int i, char **env, char **argv);
void	get_infile_outfile(t_cmd *cmd, int i, char **argv);
int		pipex(t_cmd *cmd, char **env, char **argv);

#endif