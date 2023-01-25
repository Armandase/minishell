/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:14:37 by ulayus            #+#    #+#             */
/*   Updated: 2023/01/25 15:15:44 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	check_format(char *line, char *name)
{
	if (ft_isdigit(name[0]) || check_name(name) == false)
	{
		ft_putstr_fd("bash: export: `", 2);
		write(2, line, ft_strlen(line));
		ft_putstr_fd("`: not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

static int	check_assign_symbol(char *line, char *name, t_env_list **list_var,
		t_env_list *new_var)
{
	if (ft_strchr(line, '=') == false)
	{
		new_var->export_only = true;
		if (search_var(name, list_var) == true)
			return (BREAK);
	}
	else
		new_var->export_only = false;
	if (search_var(name, list_var) == false)
		new_var->name = name;
	return (0);
}

static int	replace_value(char *name, char *value, t_env_list **list_var,
		t_env_list *new_var)
{
	t_env_list	*tmp;

	tmp = *list_var;
	while (tmp->next)
	{
		if (ft_strcmp(name, tmp->name) == false)
			return (BREAK);
		tmp = tmp->next;
	}
	if (ft_strcmp(name, tmp->name) == false
		&& search_var(name, list_var) == false)
	{
		free(tmp->value);
		tmp->value = value;
		free(name);
	}
	else
		tmp->next = new_var;
	return (0);
}

static int	add_env_var(char *line, t_env_list **list_var, char *name,
		char *value)
{
	t_env_list	*new_var;

	while (line && ft_strcmp(line, "export"))
	{
		name = export_name(line);
		value = export_value(line);
		if (check_format(line, name))
			return (1);
		if (search_var(name, list_var) == true && value && *value)
		{
			search_replace_var(name, value, list_var);
			free(name);
			return (0);
		}
		new_var = ft_calloc(1, sizeof(t_env_list));
		if (new_var == NULL)
			return (12);
		if (check_assign_symbol(line, name, list_var, new_var) == BREAK)
			return (0);
		new_var->value = value;
		new_var->next = NULL;
		if (replace_value(name, value, list_var, new_var) == BREAK)
			return (0);
	}
	return (0);
}

int	main_export(char **args, t_env_list **list_var)
{
	char	*name;
	char	*value;
	int		check;
	int		i;

	i = 0;
	name = NULL;
	value = NULL;
	if (ft_strlen_2d((const char **)args) == 1
		&& ft_strcmp(args[i], "export") == 0)
		print_args_ascii(*list_var, env_list_size(*list_var));
	while (args[i])
	{
		check = add_env_var(args[i], list_var, name, value);
		if (check != 0)
			return (check);
		i++;
	}
	return (0);
}
