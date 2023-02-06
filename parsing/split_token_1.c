/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:24:16 by ulayus            #+#    #+#             */
/*   Updated: 2023/02/05 19:02:16 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*strjoin_exit_code(int exit_code, char *line)
{
	char	*str_code;
	char	*joined_line;

	str_code = ft_itoa(exit_code);
	joined_line = ft_strjoin(str_code, line);
	free(str_code);
	return (joined_line);
}

static char	*join_line(char *tmp_str, int i, char *str, t_env_list *list_var)
{
	char	*trunc_str;
	char	*cpy_str;
	char	tmp;

	if (str[i] == '?')
	{
		trunc_str = strjoin_exit_code(g_sh_state.exit_code, str + 2);
		cpy_str = ft_strjoin(tmp_str, trunc_str);
		free(trunc_str);
		return (cpy_str);
	}
	tmp = str[i];
	str[i] = '\0';
	trunc_str = search_send_var(str + 1, &list_var);
	str[i] = tmp;
	cpy_str = ft_strjoin(tmp_str, trunc_str);
	if (cpy_str)
	{
		str = ft_strjoin(cpy_str, &str[i]);
		free(cpy_str);
	}
	else
		str = ft_strjoin(tmp_str, &str[i]);
	free(trunc_str);
	return (str);
}

void	cpy_envp_val(char **s, t_env_list *list_var, size_t *j)
{
	char	*tmp_str;
	size_t	i;
	char	tmp;

	i = *j;
	tmp = (*s)[i];
	(*s)[i] = '\0';
	tmp_str = ft_strdup((*s));
	(*s)[i] = tmp;
	(*s) += *j;
	i = 0;
	while ((*s)[i] && (*s)[i] != ' ' && (*s)[i] != '\"'
		&& (*s)[i] != '\'' && (*s)[i] != '?')
	{
		i++;
		if ((*s)[i] == '$')
			break ;
	}
	*s = join_line(tmp_str, i, (*s), list_var);
	free(tmp_str);
}

void	check_envp_val(char **s, size_t *j, t_env_list *list_var)
{
	if ((*s)[*j] == '$' && (*s)[*j + 1] && (*s)[*j + 1] != ' ')
		cpy_envp_val(s, list_var, j);
}
