#include "builtins.h"

void	main_exit(char **args, t_env_list **list_var)
{
	t_env_list	*tmp;

	while (*list_var)
	{
		tmp = *list_var;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
		*list_var = (*list_var)->next;
	}
	if (ft_strlen_2d((const char **)args) > 1)
		exit(ft_atoi(args[1]));
	else
		exit(0);
}
