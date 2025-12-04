/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:53:42 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/04 16:46:05 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>

void	ft_printf_putunbr(unsigned int n, int *count,
			const char *base, unsigned char digit_max_base);
void	ft_printf_putaddr(unsigned long long n, int *count, const char *base);
void	ft_printf_putnbr(int n, int *count);

void	ft_printf_putstr(const char *str, int *count);
void	ft_printf_putchar(unsigned char c, int *count);

int		ft_printf(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));

#endif