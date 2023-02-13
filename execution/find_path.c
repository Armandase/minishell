/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:01:46 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/11 15:24:19 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*ft_find_path(char **envp)
{
	int		i;
	char	*ret;
	size_t	len;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 4) == 0)
		{
			len = ft_strlen(envp[i]) + 1;
			ret = malloc(sizeof(char) * len);
			if (!ret)
				return (NULL);
			ft_strlcpy(ret, envp[i], len);
			return (ret);
		}
		i++;
	}
	return (NULL);
}

char	**get_path(char **envp)
{
	int		len;
	char	*tmp;
	char	*path;
	char	**directory;

	path = ft_find_path(envp);
	if (!path)
		return (NULL);
	directory = ft_split(path, ':');
	free(path);
	if (!directory)
		return (NULL);
	len = ft_strlen(directory[0]);
	tmp = ft_substr(directory[0], 5, len);
	if (!tmp)
		return (NULL);
	free(directory[0]);
	directory[0] = tmp;
	return (directory);
}

void	free_strs_except_himself(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	*strs = NULL;
}

void	cpy_path(char **cmd, char **directory)
{
	int		j;
	char	*tmp;
	char	*str;

	j = 0;
	if (!directory)
		return ;
	while (directory[j])
	{
		tmp = ft_strjoin(directory[j], "/");
		str = ft_strjoin(tmp, *cmd);
		free(tmp);
		if (access(str, X_OK) == 0)
		{
			free(*cmd);
			*cmd = ft_strdup(str);
			free(str);
			return ;
		}
		else
			free(str);
		j++;
	}
	free_strs_except_himself(cmd);
}

void	get_cmd_path(char **cmd, char **envp)
{
	char	**directories;
	int		i;

	directories = get_path(envp);
	i = 0;
	if (!directories)
	{
		while (cmd[i])
		{
			free(cmd[i]);
			i++;
		}
		cmd[0] = NULL;
		return ;
	}
	cpy_path(cmd, directories);
	ft_free_strs(directories);
}
