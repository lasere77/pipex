/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 10:01:30 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/05 17:56:57 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include "libft.h"

# include <sys/wait.h>
# include <stdio.h>

int	creat_process(char **argv, char *env[], int fd, pid_t *tab_pid, char **path);

#endif