/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 17:19:34 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/04 16:45:22 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_printf_putstr(const char *str, int *count)
{
	if (str)
		*count += write(1, str, ft_strlen(str));
	else
		*count += write(1, "(null)", 6);
}

void	ft_printf_putchar(unsigned char c, int *count)
{
	*count += write(1, &c, 1);
}
