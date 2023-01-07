/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:04:53 by adamiens          #+#    #+#             */
/*   Updated: 2023/01/06 17:49:06 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putunsigned(unsigned int nb, size_t *ret)
{
	if (nb > 9)
	{
		ft_putunsigned(nb / 10, ret);
	}
	ft_putfchar((nb % 10) + '0', ret);
}

void	ft_convert(const char *s, size_t i, size_t *ret, va_list args)
{
	if (s[i] == 'c')
		ft_putfchar(va_arg(args, int), ret);
	else if (s[i] == 's')
		ft_putfstr(va_arg(args, char *), ret);
	else if (s[i] == 'p')
		ft_fprint_addr(va_arg(args, unsigned long), ret);
	else if (s[i] == 'd' || s[i] == 'i')
		ft_putfnbr(va_arg(args, int), ret);
	else if (s[i] == 'u')
		ft_putunsigned(va_arg(args, unsigned int), ret);
	else if (s[i] == 'x')
		ft_putfnbr_base(va_arg(args, unsigned int), "0123456789abcdef", ret);
	else if (s[i] == 'X')
		ft_putfnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF", ret);
	else if (s[i] == '%')
		ft_putfchar('%', ret);
	else
	{
		write(1, &s[i - 1], 2);
		*ret = *ret + 2;
	}
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	size_t	i;
	size_t	*ret;
	size_t	cpy;

	i = 0;
	ret = &cpy;
	cpy = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			ft_convert(s, i, ret, args);
		}
		else
			ft_putfchar(s[i], ret);
		if (*ret == 0 && !s[i])
			return ((int)*ret);
		i++;
	}
	va_end(args);
	return ((int)*ret);
}
