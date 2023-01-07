/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:16:25 by adamiens          #+#    #+#             */
/*   Updated: 2022/10/03 18:37:10 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*begin;

	ret = ft_calloc(1, sizeof(t_list));
	if (!ret)
		return (NULL);
	begin = ret;
	while (lst)
	{
		ret->next = ft_calloc(1, sizeof(t_list));
		if (!ret->next)
		{
			ft_lstclear(&begin, del);
			return (begin);
		}
		ret->content = f(lst->content);
		ret = ret->next;
		lst = lst->next;
	}
	return (begin);
}
