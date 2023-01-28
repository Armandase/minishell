/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:01:09 by adamiens          #+#    #+#             */
/*   Updated: 2023/01/28 17:26:41 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	waiting_end(t_exec	*exec, t_env_list **list_var)
{
	int	wstatus;
	int	exit_code;
	int	i;

	i = 0;
	exit_code = 0;
	while (i < exec->nb_fork)
	{
		waitpid(exec->tab_pid[i], &wstatus, 0);
		if (WIFEXITED(wstatus))
			exit_code = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
			exit_code = WTERMSIG(wstatus);
		search_replace_var("?", ft_itoa(exit_code), list_var);
		i++;
	}
	if (exit_code)
		search_replace_var("?", ft_itoa(exit_code), list_var);
}

void	free_struct(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	while (cmd->prev != NULL)
		cmd = cmd->prev;
	while (cmd != NULL)
	{
		i = 0;
		if (cmd->cmd)
		{
			while (cmd->cmd[i] != NULL)
			{
				free(cmd->cmd[i]);
				i++;
			}
			free(cmd->cmd);
		}
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

int	tab_pid_len(t_cmd	*cmd)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (cmd->next != NULL)
	{
		if (cmd->token == CMD)
			ret++;
		i++;
		cmd = cmd->next;
	}
	return (ret);
}

void	execution(t_cmd *cmd, char **envp, t_env_list **list_var)
{
	t_exec	exec;
	int		tab_pipe[2][2];

	pipe(tab_pipe[0]);
	pipe(tab_pipe[1]);
	exec.nb_fork = 0;
	exec.tab_pid = ft_calloc(sizeof(int), tab_pid_len(cmd));
	exec.envp = envp;
	exec.list_var = list_var;
	while (cmd->next != NULL)
	{
		exec_cmd(&exec, cmd, tab_pipe);
		redirection_offset(&cmd);
	}
	close_pipe(tab_pipe);
	waiting_end(&exec, list_var);
	while (cmd->prev != NULL)
		cmd = cmd->prev;
	free_struct(cmd);
	free(exec.tab_pid);
}
