/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 10:48:14 by adamiens          #+#    #+#             */
/*   Updated: 2022/11/02 15:43:47 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"     

void	ft_putfnbr(int nb, size_t *ret)
{
	if (nb == -2147483648)
	{
		nb = 147483648;
		ft_putfchar('-', ret);
		ft_putfchar('2', ret);
	}
	if (nb < 0)
	{
		ft_putfchar('-', ret);
		nb *= -1;
	}	
	if (nb > 9)
	{
		ft_putfnbr(nb / 10, ret);
	}
	ft_putfchar((nb % 10) + '0', ret);
}
