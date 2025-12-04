/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 09:35:12 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/04 14:33:43 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*substr_cpy(char *str, char const *s, unsigned int start, size_t l)
{
	size_t	i;

	i = 0;
	while (s[start + i] && i < l)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
	{
		res = ft_calloc(1, sizeof(char));
		return (res);
	}
	if (ft_strlen(s + start) <= len)
		res = malloc(sizeof(char) * (ft_strlen(s + start) + 1));
	else
		res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res = substr_cpy(res, s, start, len);
	return (res);
}
