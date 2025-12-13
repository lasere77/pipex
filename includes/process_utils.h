/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:38:21 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/13 12:20:48 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_UTILS_H
# define PROCESS_UTILS_H

# include "cmd.h"
# include "ft_printf.h"

# include <sys/wait.h>
# include <stdio.h>

int		here_doc(char *limiter);

void	panic_free(t_cmd *cmd, char *str, int exit_code);
char	*get_command(t_cmd *cmd, int i, char **env);
char	do_dup2(t_cmd *cmd, int i);
int		get_status(t_cmd *cmd);

#endif