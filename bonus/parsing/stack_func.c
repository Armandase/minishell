/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:00:10 by adamiens          #+#    #+#             */
/*   Updated: 2023/01/26 15:00:13 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd	*list_new(void	*content, t_cmd *prev)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	if (!content)
		new->cmd = NULL;
	else
		new->cmd = content;
	new->next = NULL;
	if (!prev)
		new->prev = NULL;
	else
		new->prev = prev;
	new->token = 0;
	return (new);
}
