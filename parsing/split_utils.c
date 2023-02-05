/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:56:21 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/05 15:45:37 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	take_dollar_offset(char *str, size_t *i, size_t *count, int k)
{
	if (!str)
		*(i) += k - 1;
	else
	{
		*count += ft_strlen(str);
		*i += k;
	}
	free(str);
}

void	get_dollar_value(char *s,
	size_t *count, size_t *i, t_env_list *list_var)
{
	int		k;
	char	*var;
	char	*str;

	k = 1;
	var = NULL;
	if (!s[k] || s[k] == ' ' || s[k] == '\'' || s[k] == '\"')
		return ;
	while (s[k] && s[k] != ' ' && s[k] != '\'' && s[k] != '\"' && s[k] != '$')
		k++;
	var = malloc(sizeof(char) * k);
	k = 1;
	while (s[k] && s[k] != ' ' && s[k] != '\'' && s[k] != '\"' && s[k] != '$')
	{
		var[k - 1] = s[k];
		k++;
	}
	var[k - 1] = '\0';
	if (var[0] == '?')
		str = ft_itoa(g_sh_state.exit_code);
	else
		str = search_send_var(var, &list_var);
	take_dollar_offset(str, i, count, k);
	*count += ft_strlen(var);
	free(var);
}

void	iter_in_space(char *s, size_t *j)
{
	while (s[*j] && s[*j] == ' ')
		(*j)++;
}

void	cpy_byte_at_index_to_str(char *str, char *s, size_t *i, size_t *j)
{
	str[*i] = s[*j];
	(*i)++;
	(*j)++;
}

void	copy_and_free_line(t_token **token, char *s, char *tmp)
{
	if (tmp != s)
	{
		free(tmp);
		tmp = NULL;
	}
	(*token)->line = ft_strdup(s);
	if (s)
	{
		free(s);
		s = NULL;
	}
}
