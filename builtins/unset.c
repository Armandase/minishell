#include "builtins.h"

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

void	*main_unset(char **args, t_env_list **list_var)
{
	t_env_list	*to_free;
	t_env_list	*tmp;
	int			i;

	i = 1;
	while (args[i] != NULL)
	{
		if (ft_isdigit(name[0]) || !check_name(name) || name[0] == '-')
		{
			ft_putstr_fd("bash: export: `", 2);
			write(2, args[i], ft_strlen(args[i]));
			ft_putstr_fd("`: not a valid identifier\n", 2);
			return (1);
		}
		tmp = *list_var;
		while (tmp)
		{
			if (tmp->next && !ft_strcmp(tmp->next->name, args[i]))
			{
				to_free = tmp->next;
				tmp->next = NULL;
				if (to_free->next)
					tmp->next = to_free->next;
				free(to_free->name);
				free(to_free->value);
				free(to_free);
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}
