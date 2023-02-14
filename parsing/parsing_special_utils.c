/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_special_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 10:19:48 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/14 12:49:44 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**single_str_to_strs(char *str)
{
	char	**ret;

	ret = malloc(sizeof(char *) * 2);
	ret[0] = ft_strdup(str);
	ret[1] = NULL;
	return (ret);
}

void	iter_in_space(char *s, size_t *j)
{
	while (s[*j] && s[*j] == ' ')
		(*j)++;
}

char	**dup_strs_without_first(char **strs)
{
	int		i;
	char	**ret;

	i = 0;
	while (strs[i])
		i++;
	ret = malloc(sizeof(char *) * i);
	i = 1;
	while (strs[i])
	{
		ret[i - 1] = ft_strdup(strs[i]);
		i++;
	}
	ret[i - 1] = NULL;
	return (ret);
}

void	copy_special_command(t_cmd **cmd, t_token *token, t_env_list *list_var)
{
	char	**strs;
	int		i;

	strs = split_token(&token, list_var);
	i = 0;
	(*cmd)->next = list_new(single_str_to_strs(strs[i]), (*cmd));
	(*cmd) = (*cmd)->next;
	(*cmd)->token = FILES;
	i++;
	if (strs[i])
	{
		(*cmd)->next = list_new(dup_strs_without_first(strs), *cmd);
		(*cmd) = (*cmd)->next;
		(*cmd)->token = CMD;
	}
	ft_free_strs(strs);
}
