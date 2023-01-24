/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:45:14 by ulayus            #+#    #+#             */
/*   Updated: 2023/01/24 14:02:40 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	ft_swap(char **strs, int i, int j)
{
	char	*tmp;

	tmp = strs[i];
	strs[i] = strs[j];
	strs[j] = tmp;
}

static void	ft_sort_env_var(char **env_var, size_t size)
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

static void	join_with_quotes(t_env_list *list_var, char **env_var)
{
	int			i;
	t_env_list	*tmp;
	char		*line;

	i = 0;
	tmp = list_var;
	while (tmp != NULL)
	{
		if (tmp->export_only == true)
			env_var[i] = ft_strdup(tmp->name);
		else
		{
			line = ft_strjoin(tmp->name, "=\"");
			env_var[i] = ft_strjoin(line, tmp->value);
			free(line);
			line = env_var[i];
			env_var[i] = ft_strjoin(env_var[i], "\"");
			free(line);
		}
		i++;
		tmp = tmp->next;
	}
}

char	**env_export_create(t_env_list *list_var)
{
	size_t		len;
	char		**env_var;

	len = env_list_size(list_var);
	env_var = ft_calloc(sizeof(char *), len + 1);
	if (env_var == NULL)
		return (NULL);
	join_with_quotes(list_var, env_var);
	return (env_var);
}

void	print_args_ascii(t_env_list *list_var, size_t size)
{
	char	**env_var;
	int		i;

	i = 0;
	env_var = env_export_create(list_var);
	ft_sort_env_var(env_var, size);
	while (i < (int)size)
	{
		if (env_var[i][0] != '_' && env_var[i][0] != '?')
			ft_printf("declare -x %s\n", env_var[i]);
		free(env_var[i]);
		i++;
	}
	free(env_var);
}
