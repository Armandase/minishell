/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 22:37:12 by ulayus            #+#    #+#             */
/*   Updated: 2023/01/16 15:36:23 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_dispatcher(const char *format, int i, va_list ap, int fd)
{
	int	count;

	count = 0;
	if (format[i] == 'c')
		count = ft_putchar_v((char) va_arg(ap, int), fd);
	else if (format[i] == 's')
		count = ft_putstr_v(va_arg(ap, char *), fd);
	else if (format[i] == 'd' || format[i] == 'i')
		count = ft_putnbase(va_arg(ap, int), BASE_10, 1, fd);
	else if (format[i] == 'u')
		count = ft_putnbase(va_arg(ap, unsigned int), BASE_10, 1, fd);
	else if (format[i] == 'x')
		count = ft_putnbase (va_arg(ap, unsigned int), BASE_HEX_LW, 1, fd);
	else if (format[i] == 'X')
		count = ft_putnbase(va_arg(ap, unsigned int), BASE_HEX_UP, 1, fd);
	else if (format[i] == 'p')
		count = ft_print_addr(va_arg(ap, unsigned long), fd);
	else
	{
		count = ft_putchar_v('%', fd);
		if (format[i] != '%')
			count += ft_putchar_v(format[i], fd);
	}
	return (count);
}

int	ft_printf_fd(const char *format, int fd, ...)
{
	va_list	ap;
	int		i;
	int		count;

	count = 0;
	i = 1;
	if (format == NULL)
		return (-1);
	va_start(ap, fd);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count += ft_dispatcher(format, i, ap, fd);
		}
		else
			count += ft_putchar_v(format[i], fd);
		i++;
	}
	va_end(ap);
	return (count);
}
