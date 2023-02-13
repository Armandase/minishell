/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:42:33 by ulayus            #+#    #+#             */
/*   Updated: 2023/02/13 13:44:23 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*export_name_append(char *str)
{
	char	*name;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] && str[i + 1] == '='
			&& str[i + 2] && str[i + 2] != ' ')
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
		if (str[i] == '+')
			break ;
		name[i] = str[i];
		i++;
	}
	return (name);
}

static char	*new_line(char *str, char *name, char *value)
{
	char	*joined_line;
	char	*tmp;

	free(str);
	tmp = ft_strjoin("=", value);
	joined_line = ft_strjoin(name, tmp);
	free(tmp);
	return (joined_line);
}

int	append_value(char **str, t_env_list **list_var)
{
	char	*name;
	char	*value;
	char	*old_value;
	char	*joined_value;

	name = export_name_append(*str);
	if (name == NULL)
		return (0);
	value = export_value(*str);
	if (value == NULL)
		return (0);
	if (search_var(name, list_var) == true)
	{
		old_value = search_send_var(name, list_var);
		joined_value = ft_strjoin(old_value, value);
		free(old_value);
		free(value);
		search_replace_var(name, joined_value, list_var);
		free(name);
		return (1);
	}
	*str = new_line(*str, name, value);
	free(name);
	free(value);
	return (0);
}
