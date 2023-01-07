/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:16:15 by adamiens          #+#    #+#             */
/*   Updated: 2022/10/03 11:56:56 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*tofree;

	if (!lst || !del)
		return ;
	tmp = *lst;
	while (tmp)
	{
		tofree = tmp;
		tmp = tmp->next;
		del(tofree->content);
		free(tofree);
	}
	*lst = NULL;
}
