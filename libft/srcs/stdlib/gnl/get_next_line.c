/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:47:00 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/04 16:20:23 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static char	*ft_get_line(const char *buffer)
{
	char	*res;
	size_t	i;

	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\n')
		i++;
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	ft_bzero(res, i + 1);
	res = get_next_line_copy(buffer, res, i);
	return (res);
}

static char	get_read_error(ssize_t r, char **buffer)
{
	if (r == 0)
		return (1);
	if (r < 0)
	{
		free(*buffer);
		*buffer = NULL;
		return (1);
	}
	return (0);
}

static char	*read_buffer(int fd, char *buffer)
{
	char			*new;
	char			*tmp;
	ssize_t			r;

	new = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!new)
		return (NULL);
	while (1)
	{
		ft_bzero(new, BUFFER_SIZE + 1);
		r = read(fd, new, BUFFER_SIZE);
		if (get_read_error(r, &buffer))
			break ;
		tmp = buffer;
		buffer = ft_strjoin(tmp, new);
		free(tmp);
		if (is_new_line(new))
			break ;
	}
	free(new);
	return (buffer);
}

static char	*erase_line(char *buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\n')
		i++;
	j = 0;
	while (buffer[i + j])
	{
		buffer[j] = buffer[i + j];
		j++;
	}
	buffer[j] = buffer[i + j];
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char		*buffer[1024] = {NULL};
	char			*result;

	if ((fd < 0 || fd > 1023) || BUFFER_SIZE <= 0)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = read_buffer(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	result = ft_get_line(buffer[fd]);
	buffer[fd] = erase_line(buffer[fd]);
	if (!result)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	return (result);
}
