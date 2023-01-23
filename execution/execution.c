#include "execution.h"
#include <stdio.h>

void	waiting_end(t_exec	*exec)
{
	int	wstatus;
	int	exit_code;

	exec->nb_fork--;
	while (exec->nb_fork >= 0)
	{
		waitpid(exec->tab_pid[exec->nb_fork], &wstatus, 0);
		if (WIFEXITED(wstatus))
			exit_code = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
			exit_code = WTERMSIG(wstatus);
		exec->nb_fork--;
	}
	(void)exit_code;
}

void	free_struct(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	while (cmd->next != NULL)
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
		tmp = NULL;
	}
	free(cmd);
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
	waiting_end(&exec);
	while (cmd->prev != NULL)
		cmd = cmd->prev;
	free_struct(cmd);
	free(exec.tab_pid);
}
