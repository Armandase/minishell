/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_in_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:52:50 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/13 10:15:03 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_inside_quote_another_quote(char *s, size_t *j, char c)
{
	if ((s[*j] && s[*j] == c && s[(*j) + 1] == c))
	{
		while (s[*j] && s[*j] == c && s[(*j) + 1] == c)
			(*j) += 2;
		return (1);
	}
	return (0);
}

int	check_end_copy_in_quote(char from_str, char to_compare, size_t *j)
{
	if (from_str == to_compare)
	{
		(*j)++;
		return (1);
	}
	return (0);
}

int	double_quote_check(char **s, t_storage tmp, char *str, char **begin)
{
	int	i;

	i = 0;
	check_envp_val(s, tmp, begin);
	if ((*s)[*tmp.j] == '\"')
	{
		if (check_inside_quote_another_quote(*s, tmp.j, '\"'))
			return (0);
		if (!(*s)[*tmp.j] || (*s)[*tmp.j] == ' ')
			return (-1);
		(*tmp.j)++;
		check_envp_val(s, tmp, begin);
		while ((*s)[*tmp.j] && (*s)[*tmp.j] == '\"')
			(*tmp.j)++;
		while ((*s)[*tmp.j])
		{
			str[i] = (*s)[*tmp.j];
			i++;
			(*tmp.j)++;
			if (check_end_copy_in_quote((*s)[*tmp.j], '\"', tmp.j))
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
