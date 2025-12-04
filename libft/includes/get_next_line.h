/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:42:24 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/04 15:54:20 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

char	*get_next_line(int fd);

char	*get_next_line_copy(const char *buffer, char *res, unsigned int i);
int		is_new_line(char *new);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
#endif
