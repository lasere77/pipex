/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:40:13 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/13 18:22:13 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

static int	get_format(int fd, const char fmt, va_list va, int *count)
{
	const char	hex_maj[] = "0123456789ABCDEF";
	const char	hex_min[] = "0123456789abcdef";

	if (fmt == 'd' || fmt == 'i')
		ft_printf_putnbr(fd, va_arg(va, int), count);
	else if (fmt == 's')
		ft_printf_putstr(fd, va_arg(va, const char *), count);
	else if (fmt == 'c')
		ft_printf_putchar(fd, (unsigned char)va_arg(va, int), count);
	else if (fmt == 'u')
		ft_printf_putunbr(fd, va_arg(va, unsigned int), count, "0123456789");
	else if (fmt == 'x')
		ft_printf_putunbr(fd, va_arg(va, unsigned int), count, hex_min);
	else if (fmt == 'X')
		ft_printf_putunbr(fd, va_arg(va, unsigned int), count, hex_maj);
	else if (fmt == 'p')
		ft_printf_putaddr(fd, va_arg(va, unsigned long long), count, hex_min);
	else if (fmt == '%')
		ft_printf_putchar(fd, '%', count);
	else
	{
		ft_printf_putchar(fd, '%', count);
		ft_printf_putchar(fd, fmt, count);
	}
	return (2);
}

static int	print_str(int fd, const char *fmt, size_t *i, size_t *j)
{
	char	*str;
	int		count;

	count = 0;
	str = ft_substr(fmt, *j, *i - *j);
	if (!str)
		return (0);
	write(fd, str, ft_strlen(str));
	free(str);
	count += *i - *j;
	*j = *i;
	if (fmt[*i] == '%')
		*j += 2;
	return (count);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	va;
	size_t	i;
	size_t	j;
	int		count;

	if (!fmt)
		return (-1);
	va_start(va, fmt);
	i = 0;
	j = 0;
	count = 0;
	while (fmt[i])
	{
		if (fmt[i] == '\n' || fmt[i] == '%')
			count += print_str(1, fmt, &i, &j);
		if (fmt[i] == '%')
			i += get_format(1, fmt[i + 1], va, &count);
		else
			i++;
	}
	if (i != j)
		count += print_str(1, fmt, &i, &j);
	va_end(va);
	return (count);
}

int	ft_printfd(int fd, const char *fmt, ...)
{
	va_list	va;
	size_t	i;
	size_t	j;
	int		count;

	if (!fmt)
		return (-1);
	va_start(va, fmt);
	i = 0;
	j = 0;
	count = 0;
	while (fmt[i])
	{
		if (fmt[i] == '\n' || fmt[i] == '%')
			count += print_str(fd, fmt, &i, &j);
		if (fmt[i] == '%')
			i += get_format(fd, fmt[i + 1], va, &count);
		else
			i++;
	}
	if (i != j)
		count += print_str(fd, fmt, &i, &j);
	va_end(va);
	return (count);
}
