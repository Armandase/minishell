#include "execution.h"
#include <stdlib.h>
#include <unistd.h>

void	exec_free(t_cmd *cmd)
{
	int	i;
	int	j;

	print_error("Execve error", 127, cmd);
	i = 0;
	while (cmd[i].cmd != NULL)
	{
		j = 0;
		while (cmd[i].cmd[j] != NULL)
		{
			free(cmd[i].cmd[j]);
			free(cmd[i].quote);
			j++;
		}
		free(&cmd[i]);
		i++;
	}
	free(cmd->exit);
	free(cmd);
	exit(127);
}

void	inside_fork(t_cmd *cmd, int i, char **envp, int tab_pipe[2])
{
	if (i != 0 && cmd[i - 1].token == PIPE)
		dup2(cmd[i - 1].fd_out, 0);
	if (cmd[i].token == PIPE)
		dup2(tab_pipe[1], 1);
	close(tab_pipe[0]);
	close(tab_pipe[1]);
	execve(cmd[i].cmd[0], cmd[i].cmd, envp);
	exec_free(cmd);
}

void	apply_execution(t_exec *exec, int i, char **envp)
{
	int	tab_pipe[2];

	pipe(tab_pipe);
	//pipe(tab_pipe[1]);
	//if (cmd[i].token ==)
	exec->tab_pid[exec->nb_fork] = fork();
	if (exec->tab_pid[exec->nb_fork] == -1)
		print_error("Fork error", 127, exec->cmd);
	else if (exec->tab_pid[exec->nb_fork] == 0)
		inside_fork(exec->cmd, i, envp, tab_pipe);
	if (i != 0 && exec->cmd[i - 1].token == PIPE)
		dup2(tab_pipe[1], 1);
	if (exec->cmd[i].token == PIPE)
		exec->cmd[i].fd_out = tab_pipe[0];
}

void	exec_cmd(t_exec *exec, int i, char **envp, t_env_list *list_var)
{
	if (ft_strncmp(exec->cmd[i].cmd[0], "echo", 4) == 0
		|| ft_strncmp(exec->cmd[i].cmd[0], "cd", 2) == 0
		|| ft_strncmp(exec->cmd[i].cmd[0], "pwd", 3) == 0
		|| ft_strncmp(exec->cmd[i].cmd[0], "export", 6) == 0
		|| ft_strncmp(exec->cmd[i].cmd[0], "unset", 5) == 0
		|| ft_strncmp(exec->cmd[i].cmd[0], "env", 3) == 0
		|| ft_strncmp(exec->cmd[i].cmd[0], "exit", 4) == 0)
		builtins_selection(&exec->cmd[i], list_var);
	else
	{
		if (access(exec->cmd[i].cmd[0], X_OK) != 0)
		{
			get_cmd_path(&exec->cmd[i].cmd[0], envp);
			if (exec->cmd[i].cmd[0] == NULL)
			{
				print_error("Command not found", 127, exec->cmd);
				return ;
			}
		}
		apply_execution(exec, i, envp);
		exec->nb_fork++;
	}
}
