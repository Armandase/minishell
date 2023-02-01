/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:50:08 by ulayus            #+#    #+#             */
/*   Updated: 2023/02/01 13:09:24 by ulayus           ###   ########.fr       */
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

int	append_value(char *name, char *value, t_env_list **list_var)
{
	t_env_list	*tmp;
	char		*joined_str;
	int			i;

	i = 0;
	while (name[i])
		i++;
	if (name[i - 1] != '+')
		return (0);
	tmp = *list_var;
	while (tmp->next)
	{	
}
