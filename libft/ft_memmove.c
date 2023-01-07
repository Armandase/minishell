/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:59:11 by adamiens          #+#    #+#             */
/*   Updated: 2022/10/03 15:35:51 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*tmp;
	const char	*cast;

	tmp = (char *)dest;
	cast = (char *)src;
	i = 0;
	if (n && !dest && !src)
		return ((void *)dest);
	if (dest < src)
	{
		while (i < n)
		{
			tmp[i] = cast[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i--)
			tmp[i] = cast[i];
	}
	return ((void *)dest);
}
