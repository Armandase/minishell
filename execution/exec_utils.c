/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:02:09 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/06 10:38:04 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	free_list_var(t_env_list **list_var, char **envp)
{
	t_env_list	*head;
	t_env_list	*tmp;

	ft_free_strs(envp);
	envp = NULL;
	head = *list_var;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		if (tmp)
		{
			free(tmp->name);
			free(tmp->value);
			free(tmp);
		}
	}
}

void	free_stack(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		j;

	if (cmd)
	{
		while (cmd->prev != NULL)
			cmd = cmd->prev;
		while (cmd != NULL)
		{
			j = 0;
			if (cmd->cmd)
			{
				while (cmd->cmd[j] != NULL)
				{
					free(cmd->cmd[j]);
					j++;
				}
				free(cmd->cmd);
			}
			tmp = cmd;
			cmd = cmd->next;
			free(tmp);
		}
	}
}

void	exec_free(t_exec *exec, t_cmd *cmd, int exit_code)
{
	if (g_sh_state.exit_code != 130)
		g_sh_state.exit_code = exit_code;
	if (exit_code)
		perror("Error");
	free_stack(cmd);
	if (exec && exec->tab_pid)
		free(exec->tab_pid);
	free_list_var(exec->list_var, exec->envp);
	exit(exit_code);
}

void	redirection_offset(t_cmd **cmd)
{
	if (*cmd)
		*cmd = (*cmd)->next;
	if ((*cmd)->token == FILES && (*cmd)->next)
	{
		*cmd = (*cmd)->next;
		if ((*cmd)->next)
			*cmd = (*cmd)->next;
	}
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

void	close_pipe(int tab_pipe[2][2])
{
	close(tab_pipe[1][1]);
	close(tab_pipe[1][0]);
	close(tab_pipe[0][1]);
	close(tab_pipe[0][0]);
}
