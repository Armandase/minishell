#include "builtins.h"

void	*main_unset(char **args, t_env_list *list_var)
{
	t_env_list	*tmp;
	int			i;

	i = 1;
	tmp = list_var;
	while (args[i] != NULL)
	{
		while (tmp)
		{
			if (tmp->next && !ft_strcmp(tmp->next->name, args[i]))
			{
				if (tmp->next->next)
					tmp = tmp->next->next;
				free(tmp->next->name);
				free(tmp->next->value);
				free(tmp->next);
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (list_var);
}
