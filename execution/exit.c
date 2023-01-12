#include "execution.h"

void	exit_shell(t_env_list *list_var)
{
	t_env_list	*tmp;

	while (list_var != NULL)
	{
		tmp = list_var;
		list_var = list_var->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	exit(1);
}
