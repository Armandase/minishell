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

void	inside_fork(t_exec *exec, char **envp, int tab_pipe[2][2])
{
	int	ret;

	if (exec->i != 0 && exec->cmd[exec->i - 1].token == PIPE)
		dup2(tab_pipe[(exec->nb_fork - 1) % 2][0], 0);
	if (exec->cmd[exec->i].token == PIPE)
		dup2(tab_pipe[exec->nb_fork % 2][1], 1);
	close_pipe(tab_pipe);
	ret = execve(exec->cmd[exec->i].cmd[0], exec->cmd[exec->i].cmd, envp);
	if (ret == -1)
		exec_free(exec->cmd);
}

void	apply_execution(t_exec *exec, char **envp, int tab_pipe[2][2])
{
	open_pipe(tab_pipe, exec->i);
	exec->tab_pid[exec->nb_fork] = fork();
	if (exec->tab_pid[exec->nb_fork] == -1)
		print_error("Fork error", 127, exec->cmd);
	else if (exec->tab_pid[exec->nb_fork] == 0)
		inside_fork(exec, envp, tab_pipe);
}

void	exec_cmd(t_exec *exec, char **envp, t_env_list *list_var, int tab_pipe[2][2])
{
	if (ft_strncmp(exec->cmd[exec->i].cmd[0], "echo", 4) == 0
		|| ft_strncmp(exec->cmd[exec->i].cmd[0], "cd", 2) == 0
		|| ft_strncmp(exec->cmd[exec->i].cmd[0], "pwd", 3) == 0
		|| ft_strncmp(exec->cmd[exec->i].cmd[0], "export", 6) == 0
		|| ft_strncmp(exec->cmd[exec->i].cmd[0], "unset", 5) == 0
		|| ft_strncmp(exec->cmd[exec->i].cmd[0], "env", 3) == 0
		|| ft_strncmp(exec->cmd[exec->i].cmd[0], "exit", 4) == 0)
		builtins_selection(&exec->cmd[exec->i], list_var);
	else
	{
		if (access(exec->cmd[exec->i].cmd[0], X_OK) != 0)
		{
			get_cmd_path(&exec->cmd[exec->i].cmd[0], envp);
			if (exec->cmd[exec->i].cmd[0] == NULL)
			{
				print_error("Command not found", 127, exec->cmd);
				return ;
			}
		}
		apply_execution(exec, envp, tab_pipe);
		exec->nb_fork++;
	}
}
