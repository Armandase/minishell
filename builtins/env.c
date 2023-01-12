#include "builtins.h"

void	main_env(char **args, t_env_list *list_var)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		if (ft_strcmp(args[i], "env"))
		{
			ft_putstr_fd("env: '", 2);
			write(2, args[i], ft_strlen(args[i]));
			ft_putstr_fd("': No such file or directory\n", 2);
			return ;
		}
		i++;
	}
	while (list_var->next)
	{
		ft_printf("%s=%s\n", list_var->name, list_var->value);
		list_var = list_var->next;
	}
}
