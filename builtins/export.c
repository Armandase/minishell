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
	i = 0;
	while (str[j])
	{
		value[i] = str[j];
		j++;
		i++;
	}
	return (value);
}

void	*main_export(char **args, t_env_list *list_var)
{
	t_env_list	*new_var;
	char		*name;
	char		*value;
	int			i;

	i = 1;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			name = NULL;
			name = export_name(args[i]);
			value = NULL;
			value = export_value(args[i]);
			new_var = ft_calloc(1, sizeof(t_env_list));
			if (new_var == NULL)
				return (NULL); //A faire plus propre avec un ft_exit_error
			new_var->name = name;
			new_var->value = value;
			new_var->next = NULL;
			if (list_var == NULL)
				list_var = new_var;
			while (list_var->next)
				list_var = list_var->next;
			list_var->next = new_var;
		}
		i++;
	}
	return (list_var);
}
