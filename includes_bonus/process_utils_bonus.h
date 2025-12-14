/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:38:21 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/14 11:51:59 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_UTILS_BONUS_H
# define PROCESS_UTILS_BONUS_H

# include "cmd_bonus.h"

# include <sys/wait.h>
# include <stdio.h>

void	panic_free(t_cmd *cmd, char *str, int exit_code);
char	*get_command(t_cmd *cmd, int i, char **env);
char	do_dup2(t_cmd *cmd, int i);
int		get_status(t_cmd *cmd);

#endif