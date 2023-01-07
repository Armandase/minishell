/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:25:09 by adamiens          #+#    #+#             */
/*   Updated: 2023/01/07 10:09:36 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len_token(char *str, const char *delim)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (delim[j])
		{
			if (str[i] == delim[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

int	check_delim(char c, const char *delim)
{
	int	i;

	i = 0;
	while (delim[i])
	{
		if (delim[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtok(char *str, const char *delim)
{
	int			i;
	int			len;
	static char	*cpy = NULL;
	char		*token;

	i = 0;
	len = 0;
	if (str != NULL)
	{
		cpy = str;
		if (!cpy)
			return (NULL);
	}
	len = len_token(cpy, delim);
	if (len == 0)
		return (NULL);
	token = malloc(len + 1);
	token = ft_strncpy(token, cpy, len);
	token[len] = '\0';
	cpy += len;
	while (cpy && check_delim(*cpy, delim))
		cpy++;
	return (token);
}
