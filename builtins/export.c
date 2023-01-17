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

int	check_name(char *name)
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
		print_args_ascii(*list_var, env_list_size(*list_var));
	i = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			name = NULL;
			name = export_name(args[i]);
			if (ft_isdigit(name[0]) || !check_name(name) || name[0] == '-')
			{
				ft_putstr_fd("bash: export: `", 2);
				write(2, args[i], ft_strlen(args[i]));
				ft_putstr_fd("`: not a valid identifier\n", 2);
				break ;
			}
			value = NULL;
			value = export_value(args[i]);
			new_var = ft_calloc(1, sizeof(t_env_list));
			if (new_var == NULL)
				return (NULL);
			new_var->name = name;
			new_var->value = value;
			new_var->next = NULL;
			tmp = *list_var;
			while (tmp->next)
			{
				if (ft_strcmp(name, tmp->name) == 0)
					break ;
				tmp = tmp->next;
			}
			if (ft_strcmp(name, tmp->name) == 0)
			{
				free(tmp->value);
				tmp->value = value;
				free(name);
			}
			else
				tmp->next = new_var;
		}
		i++;
	}
	return (list_var);
}
