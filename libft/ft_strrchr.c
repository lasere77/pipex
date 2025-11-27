/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 09:47:54 by mcolin            #+#    #+#             */
/*   Updated: 2025/10/22 17:59:43 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	len;

	len = ft_strlen(s);
	if (s[len] == (unsigned char)c)
		return ((char *)s + len);
	while (len--)
	{
		if (s[len] == (unsigned char)c)
			return ((char *)s + len);
	}
	return (NULL);
}
