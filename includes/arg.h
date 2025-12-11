/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 23:15:36 by mewen             #+#    #+#             */
/*   Updated: 2025/12/11 15:21:32 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARG_H
# define ARG_H

# include "libft.h"

# include <fcntl.h>

char	*get_bin_path(char **path, char *name_bin);
void	free_split(char **strs);
char	**get_path(char *env[]);

#endif