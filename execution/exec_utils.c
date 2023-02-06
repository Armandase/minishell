/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:02:09 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/06 15:35:16 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	heredoc_offset(t_cmd *cmd)
{
	t_cmd	*cpy;
	int		i;

	i = 0;
	cpy = cmd;
	while (cpy->next)
	{
		if (cpy->token == CMD || cpy->token == 0)
			break ;
		if (cpy->token == HEREDOC)
		{
			while (g_sh_state.pipe_heredoc[i] == 0)
				i++;
			close(g_sh_state.pipe_heredoc[i]);
			g_sh_state.pipe_heredoc[i] = 0;
		}
		cpy = cpy->next;
	}
}

void	redirection_offset(t_cmd **cmd)
{
	if (*cmd)
		*cmd = (*cmd)->next;
	if ((*cmd)->token == FILES && (*cmd)->next)
	{
		if ((*cmd)->prev)
			heredoc_offset((*cmd)->prev);
		*cmd = (*cmd)->next;
		if ((*cmd)->next)
			*cmd = (*cmd)->next;
	}
	else
		heredoc_offset((*cmd)->prev);
	if (*cmd)
	{
		while ((*cmd)->next)
		{
			if ((*cmd)->token == CMD || (*cmd)->token == 0)
				break ;
			*cmd = (*cmd)->next;
		}
	}
}

int	verif_args(t_cmd *cmd, int check)
{
	if (check == 1 && cmd->cmd && ft_strlen(cmd->cmd[0]) == 0)
	{
		ft_putstr_fd("🤓: Wrong arguments\n", 2);
		g_sh_state.exit_code = 127;
		return (1);
	}
	if (check == 2 && cmd->cmd[0] == NULL)
	{
		ft_putstr_fd("🤓: command not found\n", 2);
		g_sh_state.exit_code = 127;
		return (1);
	}
	return (0);
}
