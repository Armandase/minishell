/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:18:00 by ulayus            #+#    #+#             */
/*   Updated: 2023/01/25 10:08:52 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*ft_strjoin_space(char *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	i = -1;
	j = 0;
	while (s1 && s1[++i])
	{
		str[j] = s1[i];
		j++;
	}
	free(s1);
	i = -1;
	while (s2 && s2[++i])
	{
		str[j] = s2[i];
		j++;
	}
	str[j] = ' ';
	str[j + 1] = '\0';
	return (str);
}
