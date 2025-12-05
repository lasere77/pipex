/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 23:15:36 by mewen             #+#    #+#             */
/*   Updated: 2025/12/05 18:24:35 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARG_H
# define ARG_H

# include "libft.h"

# include <fcntl.h>

char	**get_new_arg(char **path, char *argv);
void	free_split(char **strs);
char	*get_path(char *env[]);
int		get_nb_valid_cmd(int argc, char *argv[], char **path);

#endif