/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:08:50 by ulayus            #+#    #+#             */
/*   Updated: 2022/10/03 17:48:05 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_word(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 1;
	while (s[i] == c && s[i])
		i++;
	if (i + 1 == ft_strlen(s) || i == ft_strlen(s))
		return (0);
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] == c)
				i++;
			if (!s[i])
				return (count);
			count++;
		}
		i++;
	}
	return (count);
}

static size_t	count_char(char const *s, char c, size_t i)
{
	size_t	count;

	count = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i] && s[i] != c)
	{
		count++;
		i++;
	}
	return (count);
}

static size_t	ft_strccpy(const char *s, char *str, char c, size_t j)
{
	size_t	i;

	i = 0;
	while (s[j] == c && s[j])
		j++;
	while (s[j] && s[j] != c)
	{
		str[i] = s[j];
		i++;
		j++;
	}
	str[i] = 0;
	while (s[j] == c && s[j])
		j++;
	return (j);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**strs;

	if (!s)
		return (0);
	strs = malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (strs == NULL)
		return (0);
	i = 0;
	j = 0;
	while (s[i] && (j < count_word(s, c) + 1 && count_word(s, c)))
	{
		strs[j] = malloc(count_char(s, c, i) + 1);
		if (!strs[j])
			return (0);
		i = ft_strccpy(s, strs[j], c, i);
		j++;
	}
	strs[j] = 0;
	return (strs);
}
