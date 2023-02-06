/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:36:51 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/06 16:17:46 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	check_nb_heredoc(t_cmd *cmd, t_env_list **list_var, char **envp)
{
	t_cmd	*cpy;
	int		i;

	i = 0;
	cpy = cmd;
	while (cpy->next)
	{
		if (cpy->token == HEREDOC)
			i++;
		cpy = cpy->next;
	}
	if (i > 16)
	{
		ft_putstr_fd("Maximum here-document count exceeded.\n", 2);
		free_struct(cmd);
		free_list_var(list_var, envp);
		exit(2);
	}
}

bool	get_heredoc(t_cmd *cmd, t_env_list **list_var, char **envp)
{
	t_cmd	*cpy;
	int		i;

	i = 0;
	cpy = cmd;
	check_nb_heredoc(cmd, list_var, envp);
	while (i < 16)
		g_sh_state.pipe_heredoc[i++] = 1;
	i = 0;
	while (cpy->next)
	{
		if (cpy->token == HEREDOC && cpy->next)
		{
			cpy = cpy->next;
			g_sh_state.state = HEREDOC;
			g_sh_state.pipe_heredoc[i] = heredoc(cpy);
			if (g_sh_state.pipe_heredoc[i++] == -2)
				return (false);
		}
		else
			cpy = cpy->next;
	}
	return (true);
}

void	close_heredoc(void)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if (g_sh_state.pipe_heredoc[i] != 0 && g_sh_state.pipe_heredoc[i] != 1)
		{
			if (g_sh_state.pipe_heredoc[i] == -2)
				break ;
			close(g_sh_state.pipe_heredoc[i]);
		}
		i++;
	}
}
