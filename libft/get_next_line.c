/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 10:13:37 by adamiens          #+#    #+#             */
/*   Updated: 2022/12/12 09:33:58 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_nlcpy(char *buffer, char *str, int i)
{
	int	j;

	j = 0;
	while (buffer[j])
	{
		str[i] = buffer[j];
		if (str[i] == '\n')
		{
			i++;
			str[i] = '\0';
			return ;
		}
		i++;
		j++;
	}
	str[i] = '\0';
}

static int	ft_checkline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static int	end_file(int i, char *buffer, char *ret)
{
	if (i == 0 && buffer[0])
	{
		free(ret);
		buffer[0] = '\0';
		return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static int	i;
	static char	buffer[BUFFER_SIZE + 1];
	char		*ret;

	ret = NULL;
	if (!*buffer)
	{	
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1 || i == 0)
			return (NULL);
		buffer[i] = '\0';
	}
	ret = ft_get_strjoin(ret, buffer);
	while (!ft_checkline(ret))
	{
		if (end_file(i, buffer, ret) || i == -1)
			return (NULL);
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == 0)
			break ;
		buffer[i] = '\0';
		ret = ft_get_strjoin(ret, buffer);
	}
	ft_get_substr(buffer);
	return (ret);
}
