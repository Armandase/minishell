#include "builtins.h"

void	*main_unset(char **args, t_env_list **list_var)
{
	t_env_list	*to_free;
	t_env_list	*tmp;
	int			i;

	i = 1;
	while (args[i] != NULL)
	{
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
	return (list_var);
}
