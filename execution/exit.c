/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:53:35 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/11 15:00:25 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	exit_shell(t_env_list **list_var, char **envp)
{
	t_env_list	*head;
	t_env_list	*tmp;

	if (envp != NULL)
		ft_free_strs(envp);
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
	ft_printf("exit\n");
	exit(0);
}

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
	if (exec->fd_in > 0)
		close(exec->fd_in);
	if (exec->fd_out > 0)
		close(exec->fd_out);
	if (exit_code && g_sh_state.exit_code == 0)
		perror("Error");
	if (cmd->prev && cmd->prev->token == UN_FORK)
		exit_code = g_sh_state.exit_code;
	else
		g_sh_state.exit_code = exit_code;
	free_stack(cmd);
	if (exec && exec->tab_pid)
		free(exec->tab_pid);
	free_list_var(exec->list_var, exec->envp);
	exit(exit_code);
}
