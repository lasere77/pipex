/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:00:40 by mcolin            #+#    #+#             */
/*   Updated: 2025/11/15 12:07:47 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;

	if (!n)
		return (0);
	n--;
	i = 0;
	while (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i] && n--)
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
