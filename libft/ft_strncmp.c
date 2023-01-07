/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:42:28 by adamiens          #+#    #+#             */
/*   Updated: 2022/10/03 10:15:40 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (!n)
		return (0);
	while (*str1 == *str2 && *str1 != '\0' && *str2 != '\0' && (i < n))
	{
		str1++;
		str2++;
		i++;
	}
	if (!(i < n) && (*str1 || *str2))
		return (0);
	return (*str1 - *str2);
}
