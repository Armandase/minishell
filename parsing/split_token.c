/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:59:48 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/06 16:32:52 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static size_t	count_word(char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 1;
	while (s[i] == c && s[i])
		i++;
	if (i == ft_strlen(s))
		return (0);
	while (s[i])
	{
		if (select_quote(s, &i))
			break ;
		if (s[i] == c)
		{
			while (s[i] == c)
				i++;
			if (!s[i])
				return (count);
			count++;
		}
		else
			i++;
	}
	return (count);
}

static size_t	count_char(char *s, char c, size_t i, t_env_list *list_var)
{
	size_t	count;

	count = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (s[i] == '\'')
			count_to_next_quote(s, &i, &count, list_var);
		if (!s[i])
			break ;
		while (s[i] == '$' && s[i + 1] && s[i + 1] != '\'' && s[i + 1] != '\"')
			get_dollar_value((char *)&s[i], &count, &i, list_var);
		if (s[i] && s[i] == '\"')
			count_to_next_quote(s, &i, &count, list_var);
		if (i > ft_strlen(s) || !s[i] || s[i] == c)
			break ;
		count++;
		i++;
	}
	count += ft_strlen(s);
	return (count);
}

static char	*ft_strccpy(char *s, size_t *j, char *str, t_env_list *list_var)
{
	size_t		i;
	int			k;
	char		*begin;
	t_storage	tmp;

	i = 0;
	iter_in_space(s, j);
	begin = s;
	tmp.list_var = list_var;
	tmp.j = j;
	while (s[*j])
	{
		k = 0;
		if (s[*j] == ' ')
			break ;
		check_envp_val(&s, tmp, &begin);
		if (simple_quote_check(s, str, j, &i))
			break ;
		if (!s[*j] || s[*j] == ' ')
			break ;
		check_envp_val(&s, tmp, &begin);
		k = double_quote_check(&s, tmp, &str[i], &begin);
		check_envp_val(&s, tmp, &begin);
		if (quote_offset_and_check(k, j, &i, s))
			break ;
		cpy_byte_at_index_to_str(str, s, &i, j);
	}
	str[i] = 0;
	iter_in_space(s, j);
	return (s);
}

char	**split_token(t_token **token, t_env_list *list_var)
{
	size_t	i;
	size_t	j;
	char	**strs;
	char	*s;

	if (!token || !(*token) || !(*token)->line)
		return (0);
	s = ft_strdup((*token)->line);
	free((*token)->line);
	strs = malloc(sizeof(char *) * (count_word(s, ' ') + 1));
	if (strs == NULL)
		return (0);
	i = 0;
	j = 0;
	while (i < ft_strlen(s) && (j <= count_word(s, ' ') && count_word(s, ' ')))
	{
		strs[j] = malloc(count_char(s, ' ', i, list_var) + 1);
		if (!strs[j])
			return (0);
		s = ft_strccpy(s, &i, strs[j], list_var);
		j++;
	}
	strs[j] = 0;
	copy_and_free_line(token, s);
	return (strs);
}
