/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_in_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:52:50 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/06 16:40:33 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_inside_quote_another_quote(char *s, size_t *j, char c)
{
	while (s[*j] && s[*j] == c)
	{
		(*j)++;
		if (!s[*j] || s[*j] != c)
			return (1);
	}
	return (0);
}

int	double_quote_check(char **s, t_storage tmp, char *str, char **begin)
{
	int	i;

	i = 0;
	if ((*s)[*tmp.j] == '\"')
	{
		(*tmp.j)++;
		if (!(*s)[*tmp.j])
			return (-1);
		if ((*s)[*tmp.j] == '$' && (*s)[*tmp.j + 1] && (*s)[*tmp.j + 1] != ' '
			&& (*s)[*tmp.j + 1] != '\"')
			cpy_envp_val(s, tmp.list_var, tmp.j);
		while ((*s)[*tmp.j] && (*s)[*tmp.j] == '\"')
			(*tmp.j)++;
		while ((*s)[*tmp.j])
		{
			str[i] = (*s)[*tmp.j];
			i++;
			(*tmp.j)++;
			if (check_inside_quote_another_quote(*s, tmp.j, '\"'))
				break ;
			check_envp_val(s, tmp, begin);
		}
	}
	return (i);
}

int	quote_offset_and_check(int k, size_t *j, size_t *i, char *s)
{
	if (k == -1)
		return (1);
	else
		(*i) += k;
	if (!s[*j] || s[*j] == ' ')
		return (1);
	return (0);
}
