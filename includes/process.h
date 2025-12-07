/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 11:14:11 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/07 12:05:17 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include "cmd.h"
# include "utils.h"

# include <sys/wait.h>

int		do_child(t_cmd *cmd, int index_cmd, int fd, pid_t *list_pid);
void	wait_child(t_cmd *cmd, pid_t *list_pid);

#endif