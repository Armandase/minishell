/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:18:14 by ulayus            #+#    #+#             */
/*   Updated: 2023/01/29 17:02:54 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	check_name_unset(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (!(name[i] == '_' || ft_isalnum(name[i])))
			return (0);
		i++;
	}
	return (1);
}

static void	delete_var(t_env_list **list_var, char *name)
{
	t_env_list	*to_free;
	t_env_list	*tmp;

	tmp = *list_var;
	while (tmp)
	{
		if (tmp->next && !ft_strcmp(tmp->next->name, name))
		{
			to_free = tmp->next;
			tmp->next = NULL;
			if (to_free->next)
				tmp->next = to_free->next;
			free(to_free->name);
			free(to_free->value);
			free(to_free);
		}
		tmp = tmp->next;
	}
}

int	main_unset(char **args, t_env_list **list_var)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
	{
		if (ft_isdigit(args[i][0]) || !check_name_unset(args[i])
				|| args[i][0] == '-')
		{
			ft_putstr_fd("bash: export: `", 2);
			write(2, args[i], ft_strlen(args[i]));
			ft_putstr_fd("`: not a valid identifier\n", 2);
			return (1);
		}
		delete_var(list_var, args[i]);
		i++;
	}
	return (0);
}
