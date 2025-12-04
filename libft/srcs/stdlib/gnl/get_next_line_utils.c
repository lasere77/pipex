/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:47:54 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/04 16:19:54 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line_copy(const char *buffer, char *res, unsigned int i)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		res[j] = buffer[j];
		j++;
	}
	if (!j)
	{
		free(res);
		res = NULL;
		return (NULL);
	}
	res[j] = '\0';
	return (res);
}

int	is_new_line(char *new)
{
	size_t	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (new[i] == '\n' || !new[i])
			return (1);
		i++;
	}
	return (0);
}
