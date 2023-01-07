# include "builtins.h"

void	main_env(t_env_list *list_var)
{
	while (list_var->next)
	{
		ft_printf("%s=%s\n", list_var->name, list_var->value);
		list_var = list_var->next;
	}
}
