/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_addr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:46:13 by ulayus            #+#    #+#             */
/*   Updated: 2023/01/16 15:37:35 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_put_addr(unsigned long addr, char *base, int reset, int fd)
{
	unsigned long	size;
	static int		count_addr;

	if (reset)
		count_addr = 0;
	size = 16;
	if (addr < size)
		count_addr += ft_putchar_v(base[addr % size], fd);
	else
	{
		ft_put_addr((addr / size), base, 0, fd);
		ft_put_addr((addr % size), base, 0, fd);
	}
	return (count_addr);
}

int	ft_print_addr(unsigned long addr, int fd)
{
	int	len;

	len = 0;
	if (!addr)
	{
		len = ft_putstr_v("(nil)", fd);
		return (len);
	}
	len = ft_putstr_v("0x", fd);
	len += ft_put_addr(addr, BASE_HEX_LW, 1, fd);
	return (len);
}
