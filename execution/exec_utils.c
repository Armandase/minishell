#include "execution.h"

void	exec_free(t_exec *exec)
{
	int	i;
	int	j;

	print_error("Error", 1, NULL);
	i = 0;
	if (exec->cmd)
	{
		while (exec->cmd[i].cmd != NULL)
		{
			j = 0;
			while (exec->cmd[i].cmd[j] != NULL)
			{
				free(exec->cmd[i].cmd[j]);
				if (exec->cmd[i].quote != NULL)
				{
					free(exec->cmd[i].quote);
					exec->cmd[i].quote = NULL;
				}
				j++;
			}
			free(exec->cmd[i].cmd);
			i++;
		}
		free(exec->cmd->exit);
	}
	free(exec->cmd);
	exit(127);
}

void	print_error(char *error, int exit_code, t_cmd *cmd)
{
	perror(error);
	if (cmd)
		*(cmd->exit) = exit_code;
}

void	builtins_selection(t_cmd *cmd, t_env_list **list_var)
{
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		main_echo(cmd->cmd);
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		main_cd(cmd->cmd, list_var);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		main_pwd();
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		main_export(cmd->cmd, list_var);
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		main_unset(cmd->cmd, list_var);
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		main_env(cmd->cmd, *list_var);
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		main_exit(cmd->cmd, list_var);
}

void	open_pipe(int tab_pipe[2][2], int i)
{
	close(tab_pipe[i % 2][1]);
	close(tab_pipe[i % 2][0]);
	pipe(tab_pipe[i % 2]);
}

void	close_pipe(int tab_pipe[2][2])
{
	close(tab_pipe[1][1]);
	close(tab_pipe[1][0]);
	close(tab_pipe[0][1]);
	close(tab_pipe[0][0]);
}

void	redirection_offset(t_exec *exec)
{
	if (exec->cmd[exec->i].cmd != NULL)
	{
		if (((exec->cmd[exec->i].token == OUT
					&& (exec->i == 0 || exec->cmd[exec->i - 1].token == PIPE))
				|| (exec->i != 0 && exec->cmd[exec->i - 1].token == OUT))
			|| ((exec->cmd[exec->i].token == APPEND
					&& (exec->i == 0 || exec->cmd[exec->i - 1].token == PIPE))
				|| (exec->i != 0 && exec->cmd[exec->i - 1].token == APPEND)))
		{
			while (exec->cmd[exec->i].cmd != NULL
				&& (exec->cmd[exec->i - 1].token == OUT
					|| exec->cmd[exec->i - 1].token == APPEND))
				exec->i++;
		}
	}
}
