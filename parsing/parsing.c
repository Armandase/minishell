/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 09:54:53 by ulayus            #+#    #+#             */
/*   Updated: 2023/01/31 15:13:54 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/********************************************************/
/*	Parsing:											*/
/*	  separe la ligne avec delimiteurs(become tokens)	*/
/*	  split ces tokens par les espaces (cmd & arg)		*/
/********************************************************/

#include "parsing.h"

void	set_token_cmd(t_cmd **begin)
{
	while ((*begin)->next != NULL)
	{
		if ((*begin)->token == 0 && (*begin)->prev
			&& (*begin)->prev->token != 0 && (*begin)->prev->token != PIPE)
			(*begin)->token = FILES;
		(*begin) = (*begin)->next;
	}
	while ((*begin)->prev != NULL)
		(*begin) = (*begin)->prev;
	while ((*begin)->next != NULL)
	{
		if ((*begin)->token == 0)
			(*begin)->token = CMD;
		(*begin) = (*begin)->next;
	}
	while ((*begin)->prev != NULL)
		(*begin) = (*begin)->prev;
}

char	**cpy_without_first(char **search, char **cpy)
{
	char	**ret;
	int		len;
	int		i;
	int		j;

	len = ft_strlen_2d((const char **)cpy)
		+ ft_strlen_2d((const char **)search);
	ret = malloc(sizeof(char *) * len);
	i = 0;
	while (cpy[i])
	{
		ret[i] = ft_strdup(cpy[i]);
		i++;
	}
	j = 1;
	while (search[j])
	{
		ret[i] = ft_strdup(search[j]);
		i++;
		j++;
	}
	ret[i] = NULL;
	return (ret);
}

void	redirection_with_args(t_cmd **begin)
{
	char	**cpy;

	while ((*begin)->next)
	{
		if (((*begin)->token == IN || (*begin)->token == OUT
				|| (*begin)->token == HEREDOC || (*begin)->token == APPEND)
			&& (*begin)->next
			&& ft_strlen_2d((const char **)(*begin)->next->cmd) > 1
			&& (*begin)->prev)
		{
			cpy = cpy_without_first((*begin)->next->cmd, (*begin)->prev->cmd);
			ft_free_strs((*begin)->prev->cmd);
			(*begin)->prev->cmd = cpy;
		}
		*begin = (*begin)->next;
	}
	while ((*begin)->prev != NULL)
		*begin = (*begin)->prev;
}

t_cmd	*parsing(char *line, t_env_list *list_var)
{
	t_cmd	*begin;
	char	*current_line;

	current_line = ft_strtrim(line, " \t");
	if (ft_strlen(current_line) == 0)
	{
		free(current_line);
		return (NULL);
	}
	if (check_char(current_line))
	{
		ft_putstr_fd("syntax error near unexpected token\n", 2);
		return (NULL);
	}
	begin = get_cmd(current_line, list_var);
	set_token_cmd(&begin);
	free(current_line);
	redirection_with_args(&begin);
	return (begin);
}
