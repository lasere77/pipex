/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:00:40 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/04 14:14:56 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	if (!n)
		return (0);
	n--;
	i = 0;
	while (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i] && n--)
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
