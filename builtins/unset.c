#include "builtins.h"

void	*main_unset(char **args, t_env_list *list_var)
{
	t_env_list	*to_free;
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
				to_free = tmp->next;
				if (tmp->next->next)
					tmp = tmp->next->next;
				else
					tmp->next = NULL;
				free(to_free->name);
				free(to_free->next->value);
				free(to_free->next);
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (list_var);
}
