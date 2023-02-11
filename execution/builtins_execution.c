/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:01:57 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/08 16:37:14 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	builtins_check_pipe(t_cmd *cmd)
{
	while (cmd->prev != NULL)
		cmd = cmd->prev;
	while (cmd->next != NULL)
	{
		if (cmd->token == PIPE)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

int	builtins_without_redirect(t_cmd *cmd, t_exec *exec, int tab_pipe[2][2])
{
	cmd->token = BUILTINS;
	if (cmd->next && (cmd->token == FILES || cmd->token == CMD
			|| cmd->token == 0 || cmd->token == BUILTINS))
		cmd = cmd->next;
	if (cmd->token == HEREDOC
		|| cmd->token == IN
		|| cmd->token == OUT
		|| cmd->token == APPEND)
		open_file(exec, cmd, 1, tab_pipe);
	if (cmd->prev && (cmd->prev->token == FILES || cmd->prev->token == CMD
			|| cmd->prev->token == 0 || cmd->prev->token == BUILTINS))
		cmd = cmd->prev;
	if (cmd->cmd && cmd->cmd[0] && (ft_strcmp(cmd->cmd[0], "cd") == 0))
		g_sh_state.exit_code = main_cd(cmd->cmd, exec->list_var);
	else if (cmd->cmd && cmd->cmd[0] && (ft_strcmp(cmd->cmd[0], "exit") == 0))
	{
		close_pipe(tab_pipe);
		g_sh_state.exit_code = main_exit(cmd, exec);
	}
	else if (cmd->cmd && cmd->cmd[0] && (ft_strcmp(cmd->cmd[0], "export") == 0))
		g_sh_state.exit_code = main_export(cmd->cmd, exec->list_var);
	else if (cmd->cmd && cmd->cmd[0] && (ft_strcmp(cmd->cmd[0], "unset") == 0))
		g_sh_state.exit_code = main_unset(cmd->cmd, exec->list_var);
	close_pipe(tab_pipe);
	return (UN_FORK);
}

void	builtins_selection(t_cmd *cmd, t_exec *exec, int tab_pipe[2][2])
{
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		cmd->token = BUILTINS;
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		cmd->token = BUILTINS;
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		cmd->token = BUILTINS;
	else if (ft_strcmp(cmd->cmd[0], "export") == 0
		|| ft_strcmp(cmd->cmd[0], "unset") == 0
		|| ft_strcmp(cmd->cmd[0], "exit") == 0
		|| ft_strcmp(cmd->cmd[0], "cd") == 0)
	{
		if (builtins_check_pipe(cmd))
			cmd->token = BUILTINS;
		else
			cmd->token = builtins_without_redirect(cmd, exec, tab_pipe);
	}
}

void	exec_builtins(t_cmd *cmd, int *ret, int tab_pipe[2][2], t_exec *exec)
{
	if (cmd->cmd && cmd->cmd[0] && !(ft_strcmp(cmd->cmd[0], "echo")))
		*ret = main_echo(cmd->cmd);
	else if (cmd->cmd && cmd->cmd[0] && !(ft_strcmp(cmd->cmd[0], "pwd")))
		*ret = main_pwd();
	else if (cmd->cmd && cmd->cmd[0] && !(ft_strcmp(cmd->cmd[0], "export")))
		*ret = main_export(cmd->cmd, exec->list_var);
	else if (cmd->cmd && cmd->cmd[0] && !(ft_strcmp(cmd->cmd[0], "unset")))
		*ret = main_unset(cmd->cmd, exec->list_var);
	else if (cmd->cmd && cmd->cmd[0] && !(ft_strcmp(cmd->cmd[0], "env")))
		*ret = main_env(cmd->cmd, *exec->list_var);
	else if (cmd->cmd && cmd->cmd[0] && !(ft_strcmp(cmd->cmd[0], "cd")))
		*ret = main_cd(cmd->cmd, exec->list_var);
	else if (cmd->cmd && cmd->cmd[0] && !(ft_strcmp(cmd->cmd[0], "exit")))
	{
		close_pipe(tab_pipe);
		*ret = main_exit(cmd, exec);
	}
	close_pipe(tab_pipe);
}
