/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:50:08 by ulayus            #+#    #+#             */
/*   Updated: 2023/02/02 13:22:12 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*export_name(char *str)
{
	char	*name;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i + 1] != ' ')
			break ;
		i++;
	}
	name = ft_calloc(i + 1, 1);
	if (name == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		name[i] = str[i];
		if (name[i] == '=')
			break ;
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*export_value(char *str)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i + j])
	{
		if (str[i + j] == '=')
		{
			j = i;
			i = 0;
		}
		i++;
	}
	if (str[i] == '\0')
		return (NULL);
	value = ft_calloc(i + 1, 1);
	j++;
	i = 0;
	while (str[j])
		value[i++] = str[j++];
	value[i] = str[j];
	return (value);
}

bool	check_name(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (!(name[i] == '_' || ft_isalnum(name[i])))
			return (false);
		i++;
	}
	return (true);
}

static char	*export_name_append(char *str)
{
	char	*name;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=' && str[i + 2] != ' ')
			break ;
		i++;
	}
	if (str[i] == '\0')
		return (NULL);
	name = ft_calloc(i + 1, 1);
	if (name == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		name[i] = str[i];
		if (name[i] == '+')
			break ;
		i++;
	}
	name[i] = '\0';
	return (name);
}

int	append_value(char *str, t_env_list **list_var)
{
	char	*name;
	char	*value;
	char	*old_value;
	char	*joined_value;

	name = export_name_append(str);
	if (name == NULL)
		return (0);
	value = export_value(str);
	if (value == NULL)
		return (0);
	if (search_var(name, list_var))
	{
		old_value = search_send_var(name, list_var);
		joined_value = ft_strjoin(old_value, value);
		free(old_value);
		free(value);
		search_replace_var(name, joined_value, list_var);
		free(name);
		return (1);
	}
	free(value);
	free(name);
	return (0);
}
