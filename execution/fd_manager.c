/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:02:56 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/08 17:00:57 by adamiens         ###   ########.fr       */
/*   Updated: 2023/02/06 10:35:37 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	get_right_fd(t_exec	*exec)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if (g_sh_state.pipe_heredoc[i] != 0
			&& g_sh_state.pipe_heredoc[i] != 1)
		{
			exec->fd_in = g_sh_state.pipe_heredoc[i];
			g_sh_state.pipe_heredoc[i] = 0;
			break ;
		}
		i++;
	}
}

int	open_input(t_exec *exec, t_cmd **cpy, int check)
{
	if ((*cpy)->token == IN)
	{
		*cpy = (*cpy)->next;
		if (!*cpy)
			return (1);
		exec->fd_in = open((*cpy)->cmd[0], O_RDONLY);
		if (check != 1 && exec->fd_in > 0)
			dup2(exec->fd_in, 0);
		if (((check == 1 && exec->fd_in > 0)
				|| (*cpy)->next->token == 0) && exec->fd_in != -1)
			close(exec->fd_in);
	}
	else if ((*cpy)->token == HEREDOC)
	{
		*cpy = (*cpy)->next;
		if (!*cpy)
			return (1);
		get_right_fd(exec);
		if (check != 1 && exec->fd_in > 0)
			dup2(exec->fd_in, 0);
		if ((check == 1 && exec->fd_in > 0)
			|| (*cpy)->next->token == 0)
			close(exec->fd_in);
	}
	return (0);
}

int	open_output(t_exec *exec, t_cmd **cpy, int check)
{
	if ((*cpy)->token == OUT)
	{
		*cpy = (*cpy)->next;
		if (!*cpy)
			return (1);
		exec->fd_out = open((*cpy)->cmd[0], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (check != 1 && exec->fd_out > 0)
			dup2(exec->fd_out, 1);
		if (((check == 1 && exec->fd_out > 0)
				|| (*cpy)->next->token == 0) && exec->fd_out != -1)
			close(exec->fd_out);
	}
	else if ((*cpy)->token == APPEND)
	{
		*cpy = (*cpy)->next;
		if (!*cpy)
			return (1);
		exec->fd_out = open(*(*cpy)->cmd, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (check != 1 && exec->fd_out > 0)
			dup2(exec->fd_out, 1);
		if (((check == 1 && exec->fd_out > 0)
				|| (*cpy)->next->token == 0) && exec->fd_out != -1)
			close(exec->fd_out);
	}
	return (0);
}

void	verif_and_close_fd(t_exec *exec, t_cmd *cpy, int *fail)
{
	if (exec->fd_in == -1 || exec->fd_out == -1)
		*fail = 1;
	if (*fail == 0 && exec->fd_in != -2
		&& (cpy->next->token == IN
			|| cpy->next->token == HEREDOC
			|| (cpy->prev && cpy->prev->token == IN)))
		close(exec->fd_in);
	if (cpy->next && *fail == 0 && exec->fd_out != -2
		&& (cpy->next->token == OUT
			|| cpy->next->token == APPEND
			|| cpy->next->token == PIPE))
		close(exec->fd_out);
}

void	open_file(t_exec *exec, t_cmd *cmd, int check, int pipe_tab[2][2])
{
	t_cmd	*cpy;
	int		fail;

	cpy = cmd;
	fail = 0;
	while (cpy->next != NULL && cpy->token != CMD && cpy->token != BUILTINS)
	{
		if (open_input(exec, &cpy, check) == 1)
			return ;
		if (open_output(exec, &cpy, check) == 1)
			return ;
		verif_and_close_fd(exec, cpy, &fail);
		if (fail == 1)
			break ;
		cpy = cpy->next;
	}
	if (fail == 1)
		fail_on_open(exec, cmd, pipe_tab);
}
