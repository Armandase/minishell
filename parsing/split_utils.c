/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:56:21 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/14 12:49:46 by adamiens         ###   ########.fr       */
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

void	dollars_alone_in_the_dark(size_t *count, size_t	*i)
{
	*count += 1;
	*i += 1;
}

void	get_dollar_value(char *s,
	size_t *count, size_t *i, t_env_list *list_var)
{
	int		k;
	char	*var;
	char	*str;

	str = NULL;
	if (!s[1] || s[1] == ' ' || s[1] == '\'' || s[1] == '\"')
		return ;
	var = malloc(sizeof(char) * envp_var_len(s));
	k = 1;
	while (s[k] && s[k] != ' ' && s[k] != '\'' && s[k] != '\"' && s[k] != '$')
	{
		var[k - 1] = s[k];
		k++;
	}
	var[k - 1] = '\0';
	if (var[0] == '?')
		str = ft_itoa(g_sh_state.exit_code);
	else if (!ft_strlen(var))
		dollars_alone_in_the_dark(count, i);
	else
		str = search_send_var(var, &list_var);
	take_dollar_offset(str, i, count, k);
	*count += ft_strlen(var);
	free(var);
}

void	cpy_byte_at_index_to_str(char *str, char *s, size_t *i, size_t *j)
{
	if (s[*j] != '\'' && s[*j] != '\"')
	{
		str[*i] = s[*j];
		(*i)++;
		(*j)++;
	}
}

void	copy_and_free_line(t_token **token, char *s)
{
	(*token)->line = ft_strdup(s);
	if (s)
	{
		free(s);
		s = NULL;
	}
}
