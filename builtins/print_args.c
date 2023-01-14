#include "builtins.h"

void	ft_swap(char **strs, int i, int j)
{
	char	*tmp;

	tmp = strs[i];
	strs[i] = strs[j];
	strs[j] = tmp;
}

void	ft_sort_env_var(char **env_var, size_t size)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (i < size)
	{
		j = i + 1;
		while (j < size + 1)
		{
			if (ft_strcmp(env_var[i], env_var[j]) > 0)
				ft_swap(env_var, i, j);
			j++;
		}
		i++;
	}
}

void	print_args_ascii(char **env_var, size_t size)
{
	int	i;

	//ft_sort_env_var(env_var, size);
	i = 0;
	while (i < (int)size)
	{
		ft_printf("declare -x %s\n", env_var[i]);
		i++;
	}
}
