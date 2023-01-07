/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:46:28 by adamiens          #+#    #+#             */
/*   Updated: 2022/10/03 17:51:46 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_totalen(char const *s, char c)
{
	int	i;
	int	counter;

	counter = 1;
	i = 0;
	while (s[i] == c && s[i])
		i++;
	if (i == (int)ft_strlen(s) || i + 1 == (int)ft_strlen(s))
		return (0);
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] == c)
				i++;
			if (s[i] == '\0')
				return (counter);
			counter++;
		}
		i++;
	}
	return (counter);
}

static int	ft_wordlen(const char *str, char c, int i)
{
	int	counter;

	counter = 0;
	while (str[counter + i] != c && str[counter + i])
		counter++;
	return (counter);
}

static int	ft_skip(const char *s, char c, int i)
{
	int	ret;

	ret = 0;
	while (s[i + ret] == c)
		ret++;
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		ijk[3];

	if (!s)
		return (NULL);
	strs = malloc(sizeof(char *) * (ft_totalen(s, c) + 1));
	if (!strs)
		return (NULL);
	ijk[0] = 0;
	ijk[2] = 0;
	while (s[ijk[0]])
	{
		ijk[1] = 0;
		ijk[0] += ft_skip(s, c, ijk[0]);
		if (s[ijk[0]] == '\0')
			break ;
		strs[ijk[2]] = malloc(ft_wordlen(s, c, ijk[0]) + 1);
		if (!strs[ijk[2]])
			return (NULL);
		while (s[ijk[0]] != c && s[ijk[0]])
			strs[ijk[2]][ijk[1]++] = s[ijk[0]++];
		strs[ijk[2]++][ijk[1]] = '\0';
	}
	strs[ijk[2]] = NULL;
	return (strs);
}
