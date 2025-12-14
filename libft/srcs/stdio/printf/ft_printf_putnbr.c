/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnbr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:30:42 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/04 16:46:11 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_putnbr(int fd, int n, int *count)
{
	char	a;

	if (n == -2147483648)
	{
		*count += write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		*count += write(fd, "-", 1);
		n *= -1;
	}
	if (n <= 9)
	{
		a = n + '0';
		*count += write(fd, &a, 1);
	}
	else
	{
		ft_printf_putnbr(fd, n / 10, count);
		a = n % 10 + '0';
		*count += write(fd, &a, 1);
	}
}

void	ft_printf_putunbr(int fd, unsigned int n, int *count, const char *base)
{
	unsigned int	digit_max_base;

	digit_max_base = ft_strlen(base);
	if (n <= digit_max_base - 1)
		*count += write(fd, &base[n % digit_max_base], 1);
	else
	{
		ft_printf_putunbr(fd, n / digit_max_base, count, base);
		*count += write(fd, &base[n % digit_max_base], 1);
	}
}

void	ft_printf_putaddr(int fd, unsigned long long n, int *count,
						const char	*base)
{
	if (!n)
	{
		*count += write(fd, "(nil)", 5);
		return ;
	}
	if (n <= 15)
	{
		*count += write(fd, "0x", 2);
		*count += write(fd, &base[n % 16], 1);
	}
	else
	{
		ft_printf_putaddr(fd, n / 16, count, base);
		*count += write(fd, &base[n % 16], 1);
	}
}
