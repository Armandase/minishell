/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:16:46 by adamiens          #+#    #+#             */
/*   Updated: 2022/10/03 18:38:29 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!len || !s)
		return (ft_calloc(1, 1));
	if (start >= ft_strlen(s))
		return (ft_calloc(1, 1));
	while (len - start > ft_strlen(s))
		len--;
	if (len + start > ft_strlen(s))
		len = ft_strlen(s) - start;
	i = 0;
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (i < len && s[start])
	{
		str[i] = s[start++];
		i++;
	}
	str[i] = '\0';
	return (str);
}
