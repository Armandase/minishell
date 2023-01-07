# include "builtins.h"

void	main_env(char *env[])
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_printf("%s", env[i]);
		i++;
	}
}
