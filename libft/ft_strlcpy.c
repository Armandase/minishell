/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 12:10:41 by adamiens          #+#    #+#             */
/*   Updated: 2022/10/03 19:02:29 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	lensrc;

	lensrc = ft_strlen(src);
	if (size == 0)
		return (lensrc);
	while (--size && *src)
	{
		*dst++ = *src++;
	}
	*dst = '\0';
	return (lensrc);
}
