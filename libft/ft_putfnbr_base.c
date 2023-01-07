/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfnbr_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 12:20:56 by adamiens          #+#    #+#             */
/*   Updated: 2022/11/02 15:43:34 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_fstrlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putfnbr_base(unsigned int nb, char *base, size_t *ret)
{
	unsigned int	size;
	unsigned long	number;

	number = nb;
	size = ft_fstrlen(base);
	if (number < size)
		ft_putfchar(base[number % size], ret);
	else
	{
		ft_putfnbr_base((number / size), base, ret);
		ft_putfnbr_base((number % size), base, ret);
	}
}
