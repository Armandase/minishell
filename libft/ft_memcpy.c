/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:52:48 by adamiens          #+#    #+#             */
/*   Updated: 2022/10/03 15:34:25 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*tmp;
	char	*ret;

	tmp = (char *)src;
	ret = (char *)dest;
	i = 0;
	if ((!dest && !src) && n)
		return (0);
	while (i < n)
	{
		ret[i] = tmp[i];
		i++;
	}
	return (dest);
}
