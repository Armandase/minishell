/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:02:56 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/06 10:35:37 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	open_pipe(int tab_pipe[2][2], int i)
{
	close(tab_pipe[i % 2][1]);
	close(tab_pipe[i % 2][0]);
	pipe(tab_pipe[i % 2]);
}

void	fail_on_open(t_exec *exec, t_cmd *cmd, int pipe_tab[2][2])
{
	if (exec->fd_in > 0)
		close(exec->fd_in);
	if (exec->fd_out > 0)
		close(exec->fd_out);
	close_pipe(pipe_tab);
	exec_free(exec, cmd, 1);
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
		if ((check == 1 && exec->fd_in > 0))
			close(exec->fd_in);
	}
	else if ((*cpy)->token == HEREDOC)
	{
		*cpy = (*cpy)->next;
		if (!*cpy)
			return (1);
		g_sh_state.state = HEREDOC;
		exec->fd_in = heredoc(*cpy);
		if (check != 1 && exec->fd_in > 0)
			dup2(exec->fd_in, 0);
		if ((check == 1 && exec->fd_in > 0)
			|| ((*cpy)->next && (*cpy)->next->token == 0))
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
		else if (check == 1 && exec->fd_out > 0)
			close(exec->fd_out);
	}
	else if ((*cpy)->token == APPEND)
	{
		*cpy = (*cpy)->next;
		if (!*cpy)
			return (1);
		exec->fd_out = open((*cpy)->cmd[0],
				O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (check != 1 && exec->fd_out > 0)
			dup2(exec->fd_out, 1);
		else if (check == 1 && exec->fd_out > 0)
			close(exec->fd_out);
	}
	return (0);
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
		if (exec->fd_in == -1 || exec->fd_out == -1)
			fail = 1;
		else if (cpy->next && fail == 0 && exec->fd_in != -2
			&& (cpy->next->token == IN || cpy->next->token == HEREDOC || (cpy->prev && cpy->prev->token == IN)))
			close(exec->fd_in);
		else if (cpy->next && fail == 0 && exec->fd_out != -2
			&& (cpy->next->token == OUT || cpy->next->token == APPEND))
			close(exec->fd_out);
		if (fail == 1)
			break ;
		cpy = cpy->next;
	}
	if (fail == 1)
		fail_on_open(exec, cmd, pipe_tab);
}
