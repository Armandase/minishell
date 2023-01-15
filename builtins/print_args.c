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

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
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
	ft_sort_env_var(env_var, size);
	while (i < (int)size)
	{
		if (env_var[i][0] != '_')
			ft_printf("declare -x %s\n", env_var[i]);
		free(env_var[i]);
		i++;
	}
	free(env_var[i]);
	free(env_var);
}
