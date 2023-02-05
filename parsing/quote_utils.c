/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 09:59:31 by ulayus            #+#    #+#             */
/*   Updated: 2023/02/05 14:01:49 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	find_next_quote(char *str, char c)
{
	int	i;

	i = 0;
	if (str[i] == c)
		return (i);
	while (str[i] != '\0')
	{
		i++;
		if (str[i] && str[i] == c)
			return (i);
	}
	return (-1);
}

void	quote_offset(size_t *i, int *tmp, char *s, char c)
{
	(*i)++;
	*tmp = find_next_quote(&s[*i], c);
	*i += *tmp;
}

int	select_quote(char *s, size_t *i)
{
	int	tmp;

	tmp = 0;
	if (s[*i] == '\'')
		quote_offset(i, &tmp, s, '\'');
	if (!s[*i])
		return (1);
	if (s[*i] == '\"')
		quote_offset(i, &tmp, s, '\"');
	if (!s[*i])
		return (1);
	return (0);
}

void	count_to_next_quote(char *s, size_t *i, size_t *count,
		t_env_list *list_var)
{
	int		tmp;
	char	c;
	int		j;

	j = 0;
	c = s[*i];
	(*i)++;
	tmp = find_next_quote(&s[*i], c);
	if (tmp == 0)
		*i += tmp + 1;
	else
	{
		while (s[*i + j])
		{
			if (c == '\"' && s[*i + j] == '$')
				while (s[*i + j] == '$' && s[*i + j + 1]
					&& s[*i + j + 1] != '\'' && s[*i + j + 1] != '\"'
					&& s[*i + j + 1] != ' ')
					get_dollar_value((char *)&s[*i + j], count, i, list_var);
			j++;
		}
		*count += tmp;
		*i += tmp;
	}
}

int	simple_quote_check(char *s, char *str, size_t *j, size_t *i)
{
	if (s[*j] == '\'')
	{
		(*j)++;
		if (!s[*j])
			return (1);
		while (s[*j] && s[*j] == '\'')
			(*j)++;
		while (s[*j])
		{
			str[*i] = s[*j];
			(*j)++;
			(*i)++;
			if (check_inside_quote_another_quote(s, j, '\''))
				break ;
			if (s[*j] == '\'')
			{
				(*j)++;
				break ;
			}
		}
	}
	return (0);
}
