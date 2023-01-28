/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:46:50 by ulayus            #+#    #+#             */
/*   Updated: 2023/01/24 13:46:50 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env_list	*add_var(t_env_list *list_var, char *name, char *value)
{
	t_env_list	*tmp;
	t_env_list	*new_var;

	tmp = list_var;
	new_var = ft_calloc(1, sizeof(t_env_list));
	if (new_var == NULL)
		return (NULL);
	new_var->name = name;
	new_var->value = value;
	new_var->next = NULL;
	if (list_var == NULL)
		return (new_var);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_var;
	return (list_var);
}

char	*extract_name(char *str)
{
	char	*name;
	int		i;

	i = 0;
	while (str[i] != '=')
		i++;
	name = ft_calloc(i + 1, 1);
	if (name == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '=')
	{
		name[i] = str[i];
		i++;
	}
	return (name);
}

char	*extract_value(char *str)
{
	char	*value;
	size_t	len;
	int		i;
	int		j;

	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	len = 0;
	while (str[i++])
		len++;
	value = ft_calloc(len + 1, 1);
	if (value == NULL)
		return (NULL);
	i -= len + 1;
	j = 0;
	while (str[i])
	{
		value[j] = str[i];
		i++;
		j++;
	}
	return (value);
}

t_env_list	*create_env_list(char **envp)
{
	t_env_list	*list_var;	
	char		*name;
	char		*value;
	int			i;

	i = 0;
	list_var = NULL;
	while (envp[i])
	{
		name = extract_name(envp[i]);
		value = extract_value(envp[i]);
		if (name == NULL || value == NULL)
			return (NULL);
		list_var = add_var(list_var, name, value);
		i++;
	}
	return (list_var);
}
