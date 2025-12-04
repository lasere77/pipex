/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:30:56 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/04 14:32:27 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	get_result(char *dst, char *src, unsigned int size)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = ft_strlen(src);
	while (dst && dst[j] && size > j)
		j++;
	return (i + j);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	res;

	res = get_result(dst, (char *)src, size);
	if (size == 0)
		return (res);
	size--;
	j = ft_strlen(dst);
	i = 0;
	while (src[i] && size > (j + i))
	{
		dst[j + i] = src[i];
		i++;
	}
	dst[j + i] = '\0';
	return (res);
}
