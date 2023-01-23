#include "builtins.h"

int	check_option(char *arg)
{
	size_t	i;

	i = 1;
	if (arg[0] == '-')
	{
		while (arg[i] && arg[i] == 'n')
			i++;
		if (i == ft_strlen(arg) && i > 1)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

int	main_echo(char **args)
{
	int		i;
	bool	no_newline;		

	no_newline = false;
	if (ft_strlen_2d((const char **)args) == 1)
	{
		ft_printf("\n");
		return (0);
	}
	i = 1;
	while (args[i] && check_option(args[i]))
	{
		no_newline = true;
		i++;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (no_newline == false)
		ft_printf("\n");
	return (0);
}
