#include "builtins.h"

int	main_env(char **args, t_env_list *list_var)
{
	t_env_list	*tmp;

	i = 0;
	if (ft_strlen_2d(args) > 1)
		return (2);
	tmp = list_var;
	while (tmp)
	{
		if (tmp->export_only == false)
			ft_printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}
