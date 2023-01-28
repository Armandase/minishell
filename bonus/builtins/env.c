/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:17:52 by ulayus            #+#    #+#             */
/*   Updated: 2023/01/24 14:17:53 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	main_env(char **args, t_env_list *list_var)
{
	t_env_list	*tmp;

	if (ft_strlen_2d((const char **)args) > 1)
		return (2);
	tmp = list_var;
	while (tmp)
	{
		if (tmp->export_only == false && tmp->name[0] != '?')
			ft_printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
