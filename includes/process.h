/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:08:53 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/11 17:31:54 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include "cmd.h"

# include <sys/wait.h>
# include <stdio.h>

int		pipex(t_cmd *cmd, char **env);
void	do_child(t_cmd *cmd, int i, char **env);
void	do_dup2(t_cmd *cmd, int i);
int		get_status(t_cmd *cmd);

void	panic_free(t_cmd *cmd, char *str);

#endif