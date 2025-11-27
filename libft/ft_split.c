/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:55:29 by mcolin            #+#    #+#             */
/*   Updated: 2025/11/27 09:31:56 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ult_strlen(char const *str, char c)
{
	unsigned int	i;
	unsigned int	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (res);
		res++;
		i++;
	}
	return (res);
}

static int	count_word(char const *str, char c)
{
	unsigned int	i;
	unsigned int	len;
	unsigned int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		len = ult_strlen(str + i, c);
		if (len)
		{
			count++;
			i += len;
		}
		else
			i++;
	}
	return (count);
}

static unsigned char	set_word(char const *str, char c, char **tab)
{
	unsigned int	i;
	unsigned int	len;
	unsigned int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		len = ult_strlen(str + i, c);
		if (len)
		{
			tab[count] = ft_calloc(len + 1, sizeof(char));
			if (!tab[count])
				return (1);
			ft_memcpy(tab[count], str + i, len);
			count++;
			i += len;
		}
		else
			i++;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char			**res;
	unsigned int	nb_word;
	unsigned int	i;

	if (!s)
		return (NULL);
	nb_word = count_word(s, c);
	res = ft_calloc((nb_word + 1), sizeof(char *));
	if (!res)
		return (NULL);
	if (set_word(s, c, res))
	{
		i = 0;
		while (res[i])
			free(res[i++]);
		free(res);
		return (NULL);
	}
	return (res);
}
