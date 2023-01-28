/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:53:35 by adamiens          #+#    #+#             */
/*   Updated: 2023/01/25 16:53:38 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	exit_shell(t_env_list **list_var, char **envp)
{
	t_env_list	*head;
	t_env_list	*tmp;

	if (envp != NULL)
		ft_free_strs(envp);
	head = *list_var;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		if (tmp)
		{
			free(tmp->name);
			free(tmp->value);
			free(tmp);
		}
	}
	ft_printf("exit\n");
	exit(1);
}
