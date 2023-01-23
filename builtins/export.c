#include "builtins.h"

char	*export_name(char *str)
{
	char	*name;
	int		i;

	i = 0; while (str[i])
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
	if (value == NULL)
		return (NULL);
	j++;
	i = 0;
	while (str[j])
	{
		value[i] = str[j];
		j++;
		i++;
	}
	value[i] = str[j];
	return (value);
}

static int	check_name(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (!(name[i] == '_' || name[i] == '-' || ft_isalnum(name[i])))
			return (0);
		i++;
	}
	return (1);
}

void	*main_export(char **args, t_env_list **list_var)
{
	t_env_list	*tmp;
	t_env_list	*new_var;
	char		*name;
	char		*value;
	int			i;

	if (ft_strlen_2d((const char **)args) == 1
		&& ft_strcmp(args[0], "export") == 0)
	{
		print_args_ascii(*list_var, env_list_size(*list_var));
		return (0);
	}
	i = 0;
	while (args[i])
	{
		while (ft_strcmp(args[i], "export"))
		{
			name = NULL;
			name = export_name(args[i]);
			if (ft_isdigit(name[0]) || !check_name(name) || name[0] == '-')
			{
				ft_putstr_fd("bash: export: `", 2);
				write(2, args[i], ft_strlen(args[i]));
				ft_putstr_fd("`: not a valid identifier\n", 2);
				return (1); 
			}
			value = NULL;
			value = export_value(args[i]);
			if (search_var(name, list_var) == true)
			{
				search_replace_var(name, value, list_var);
				break ;
			}
			new_var = ft_calloc(1, sizeof(t_env_list));
			if (new_var == NULL)
				return (12);
			if (ft_strchr(args[i], '=') == false)
			{
				new_var->export_only = true;
				if (search_var(name, list_var) == true)
					break ;
			}
			else
				new_var->export_only = false;
			if (search_var(name, list_var) == false)
				new_var->name = name;
			new_var->value = value;
			new_var->next = NULL;
			tmp = *list_var;
			while (tmp->next)
			{
				if (ft_strcmp(name, tmp->name) == false)
					break ;
				tmp = tmp->next;
			}
			if (ft_strcmp(name, tmp->name) == false && search_var(name, list_var) == false)
			{
				free(tmp->value);
				tmp->value = value;
				free(name);
			}
			else
				tmp->next = new_var;
			break ;
		}
		i++;
	}
	return (0);
}
