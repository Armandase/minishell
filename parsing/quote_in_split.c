/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_in_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:52:50 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/05 13:57:47 by adamiens         ###   ########.fr       */
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

int	double_quote_check(char **s, size_t *j, t_env_list *list_var, char *str)
{
	int	i;

	i = 0;
	if ((*s)[*j] == '\"')
	{
		(*j)++;
		if (!(*s)[*j])
			return (-1);
		if ((*s)[*j] == '$' && (*s)[*j + 1] && (*s)[*j + 1] != ' '
			&& (*s)[*j + 1] != '\"')
			cpy_envp_val(s, list_var, j);
		while ((*s)[*j] && (*s)[*j] == '\"')
			(*j)++;
		while ((*s)[*j])
		{
			str[i] = (*s)[*j];
			i++;
			(*j)++;
			if (check_inside_quote_another_quote(*s, j, '\"'))
				break ;
			check_envp_val(s, j, list_var);
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
