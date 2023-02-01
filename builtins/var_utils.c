/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:39:22 by ulayus            #+#    #+#             */
/*   Updated: 2023/01/29 16:45:01 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

size_t	env_list_size(t_env_list *list_var)
{
	t_env_list	*tmp;
	size_t		len;

	tmp = list_var;
	len = 0;
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}

char	**env_export(t_env_list *list_var)
{
	t_env_list	*tmp;
	size_t		len;
	char		**env_var;
	char		*line;
	int			i;

	len = env_list_size(list_var);
	env_var = ft_calloc(sizeof(char *), len + 1);
	if (env_var == NULL)
		return (NULL);
	i = 0;
	tmp = list_var;
	while (tmp != NULL)
	{
		line = ft_strjoin(tmp->name, "=");
		env_var[i] = ft_strjoin(line, tmp->value);
		free(line);
		tmp = tmp->next;
		i++;
	}
	return (env_var);
}

bool	search_var(char *var, t_env_list **list_var)
{
	t_env_list	*tmp;
	int			i;

	tmp = *list_var;
	i = 0;
	while (tmp)
	{
		if (ft_strcmp(var, tmp->name) == false)
			return (true);
		tmp = tmp->next;
		i++;
	}
	return (false);
}

char	*search_send_var(char *var, t_env_list **list_var)
{
	t_env_list	*tmp;
	int			i;

	tmp = *list_var;
	i = 0;
	while (tmp)
	{
		if (ft_strcmp(var, tmp->name) == 0)
		{
			var = ft_strdup(tmp->value);
			return (var);
		}
		tmp = tmp->next;
		i++;
	}
	return (NULL);
}

void	search_replace_var(char *name, char *value, t_env_list **list_var)
{
	t_env_list	*tmp;

	tmp = *list_var;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == false)
		{
			free(tmp->value);
			tmp->value = value;
			return ;
		}
		tmp = tmp->next;
	}
	free(value);
}
