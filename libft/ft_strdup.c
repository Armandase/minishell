/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:04:19 by adamiens          #+#    #+#             */
/*   Updated: 2022/10/03 15:34:14 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		size;
	char	*str;

	size = 0;
	while (s[size] != '\0')
		size++;
	str = (char *) malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	size = 0;
	while (s[size] != '\0')
	{
		str[size] = s[size];
		size++;
	}
	str[size] = '\0';
	return (str);
}
