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

void	ft_printf_putnbr(int n, int *count)
{
	char				a;

	if (n == -2147483648)
	{
		*count += write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		*count += write(1, "-", 1);
		n *= -1;
	}
	if (n <= 9)
	{
		a = n + '0';
		*count += write(1, &a, 1);
	}
	else
	{
		ft_printf_putnbr(n / 10, count);
		a = n % 10 + '0';
		*count += write(1, &a, 1);
	}
}

void	ft_printf_putunbr(unsigned int n, int *count,
	const char *base, unsigned char digit_max_base)
{
	if (n <= digit_max_base - 1)
		*count += write(1, &base[n % digit_max_base], 1);
	else
	{
		ft_printf_putunbr(n / digit_max_base, count, base, digit_max_base);
		*count += write(1, &base[n % digit_max_base], 1);
	}
}

void	ft_printf_putaddr(unsigned long long n, int *count, const char	*base)
{
	if (!n)
	{
		*count += write(1, "(nil)", 5);
		return ;
	}
	if (n <= 15)
	{
		*count += write(1, "0x", 2);
		*count += write(1, &base[n % 16], 1);
	}
	else
	{
		ft_printf_putaddr(n / 16, count, base);
		*count += write(1, &base[n % 16], 1);
	}
}
