/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:58:04 by adamiens          #+#    #+#             */
/*   Updated: 2022/10/03 19:04:21 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_inset(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_begin(char const *s1, char const *set)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		if (ft_inset(set, s1[i]) == 1)
			j++;
		else
			return (j);
		i++;
	}
	return (j);
}

static int	ft_end(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = (int)ft_strlen((char *)s1) - 1;
	while (i < j)
	{
		if (ft_inset(set, s1[j]) == 1)
			i++;
		else
			return (i);
		j--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	char	*str;
	size_t	j;
	size_t	start;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = 0;
	start = ft_begin(s1, set);
	if (start != ft_strlen(s1))
		j = ft_strlen(s1) - (ft_begin(s1, set) + ft_end(s1, set));
	str = malloc(j + 1);
	if (!str)
		return (NULL);
	while (i < j)
	{
		str[i] = s1[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
