#include "builtins.h"

void	main_env(char **args, t_env_list *list_var)
{
	t_env_list	*tmp;
	int			i;

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
	tmp = list_var;
	while (tmp)
	{
		ft_printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}
