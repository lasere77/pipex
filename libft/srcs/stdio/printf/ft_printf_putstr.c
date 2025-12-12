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

void	ft_printf_putstr(int fd, const char *str, int *count)
{
	if (str)
		*count += write(fd, str, ft_strlen(str));
	else
		*count += write(fd, "(null)", 6);
}

void	ft_printf_putchar(int fd, unsigned char c, int *count)
{
	*count += write(fd, &c, 1);
}
