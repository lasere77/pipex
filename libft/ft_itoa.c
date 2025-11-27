/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:18:18 by mcolin            #+#    #+#             */
/*   Updated: 2025/10/21 16:15:34 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned char	get_itoa_len(int nb)
{
	unsigned char	res;

	res = 0;
	if (nb < 0)
		res++;
	while (nb)
	{
		res++;
		nb /= 10;
	}
	return (res);
}

static char	*specific_itoa(int n)
{
	char	*res;

	res = NULL;
	if (!n)
		res = ft_strdup("0");
	if (n == -2147483648)
		res = ft_strdup("-2147483648");
	return (res);
}

char	*ft_itoa(int n)
{
	unsigned char	i;
	char			*res;

	if (!n || n == -2147483648)
	{
		res = specific_itoa(n);
		return (res);
	}
	i = get_itoa_len(n);
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	if (n < 0)
		n = -n;
	res[i--] = '\0';
	while (n)
	{
		res[i--] = (n % 10) + '0';
		n /= 10;
	}
	if (!i)
		res[i] = '-';
	return (res);
}
