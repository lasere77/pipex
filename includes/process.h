/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mewen <mewen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 10:01:30 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/01 23:27:57 by mewen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include "libft.h"

# include <sys/wait.h>
# include <stdio.h>

int	creat_process(char **argv, char *env[], int fd);

#endif