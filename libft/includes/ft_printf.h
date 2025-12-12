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
# include "libft.h"

void	ft_printf_putunbr(int fd, unsigned int n, int *count, const char *base);
void	ft_printf_putaddr(int fd, unsigned long long n, int *count,
			const char *base);
void	ft_printf_putnbr(int fd, int n, int *count);

void	ft_printf_putstr(int fd, const char *str, int *count);
void	ft_printf_putchar(int fd, unsigned char c, int *count);

int		ft_printf(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
int		ft_printfd(int fd, const char *fmt, ...);

#endif