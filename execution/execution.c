#include "execution.h"
#include <stdio.h>

void	waiting_end(t_exec	*exec)
{
	int	wstatus;

	exec->nb_fork--;
	while (exec->nb_fork >= 0)
	{ 
		waitpid(exec->tab_pid[exec->nb_fork], &wstatus, 0);
		if (WIFEXITED(wstatus))
			*exec->cmd->exit = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
			*exec->cmd->exit = WTERMSIG(wstatus);
		exec->nb_fork--;
	}
}

int	tab_pid_len(t_cmd	*cmd)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	ret = 0;
	while (cmd[i].cmd != NULL)
	{
		j = 0;
		while (cmd[i].cmd[j] != NULL)
		{
			j++;
			ret++;
		}
		i++;
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
	exec.i = 0;
	exec.cmd = cmd;
	exec.fd_out = -1;
	exec.tab_pid = ft_calloc(sizeof(int), tab_pid_len(cmd));
	while (cmd[exec.i].cmd != NULL)
	{
		//if (cmd[i].token == PIPE || cmd[i].token == 0)
		exec_cmd(&exec, envp, list_var, tab_pipe);
		exec.i++;
		redirection_offset(&exec);
	}
	close_pipe(tab_pipe);
	waiting_end(&exec);
}
