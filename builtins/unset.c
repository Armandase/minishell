#include "builtins.h"

t_env_list	*main_unset(char *arg_name, t_env_list *list_var)
{
	t_env_list	*tmp;

	tmp = list_var;
	while (tmp->next)
	{
		if (tmp->next && !ft_strcmp(tmp->next->name, arg_name))
		{
			free(tmp->next);
			if (tmp->next->next)
				tmp = tmp->next->next;
		}
		tmp = tmp->next;
	}
	return (list_var);
}
