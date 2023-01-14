#include "execution.h"

void	exit_shell(t_env_list **list_var)
{
	t_env_list	*tmp;

	tmp = *list_var;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	exit(1);
}
