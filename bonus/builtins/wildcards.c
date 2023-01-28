/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:43:04 by ulayus            #+#    #+#             */
/*   Updated: 2023/01/28 17:49:42 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	process_file(char *file_name, char *wildcard, int *i, int *j)
{
	while (wildcard[*j] && file_name[*i] && wildcard[*j] == file_name[*i])
	{
		if (wildcard[*j] == '*')
			return (BREAK);
		(*i)++;
		(*j)++;
	}
	if (wildcard[*j] != file_name[*i] && (wildcard[*j] != '*' && *j == 0))
		return (false);
	else
	{
		while (wildcard[*j] == '*' && wildcard[*j + 1])
			(*j)++;
		while (wildcard[*j] && file_name[*i] && wildcard[*j] != file_name[*i])
			i++;
		if (file_name[*i] == '\0' && wildcard[*j] != '*'
			&& wildcard[*j] != file_name[*i])
			return (false);
	}
}

bool	search_file_name(char *file_name, char *wildcard)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (file_name[0] == '.' && wildcard[0] != '.')
		return (false);
	while (file_name[i])
	{
		if (process_file(file_name, wildcard, &i, &j) == false)
			return (false);
	}
	return (true);
}

int	main_wildcards(char **args)
{
	char			pwd[4096];
	struct dirent	*dir_ent;
	DIR				*dir;	
	char			*joined_files;
	size_t			nb_files;

	joined_files = NULL;
	getcwd(pwd, 4096);
	dir = opendir(pwd);
	if (dir == NULL)
		return (1);
	dir_ent = readdir(dir);
	joined_files = ft_strjoin_space(joined_files, args[0]);
	joined_files = ft_strjoin_space(joined_files, args[1]);
	while (dir_ent != NULL)
	{
		if (search_file_name(dir_ent->d_name, args[1]) == true)
			joined_files = ft_strjoin_space(joined_files, dir_ent->d_name);
		dir_ent = readdir(dir);
	}
	ft_free_strs(args);
	args = ft_split(joined_files, 1);
	free(joined_files);
	closedir(dir);
	return (0);
}
