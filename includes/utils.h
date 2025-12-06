/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:41:41 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/06 20:17:52 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cmd.h"
# include "arg.h"

# include <stdio.h>
# include <fcntl.h>

void	write_in_file(char *file_path, int fd);
int		open_input_file(char *file_path);
void	free_split(char **strs);
char	is_last_cmd_valid(int argc, char *argv[], char *env[]);
void	panic_free(t_cmd *cmd, pid_t *list_pid);

#endif