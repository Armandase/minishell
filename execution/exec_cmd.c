#include "execution.h"
#include <stdio.h>

void	open_file(t_exec *exec)
{
	int	fail;
	int	fd;

	exec->i++;
	fail = 0;
	while (exec->cmd[exec->i].cmd != NULL
		&& (exec->cmd[exec->i - 1].token == OUT
			|| exec->cmd[exec->i - 1].token == APPEND))
	{
		if (fail == 0)
		{
			if (exec->cmd[exec->i - 1].token == OUT)
				fd = open(exec->cmd[exec->i].cmd[0],
						O_WRONLY | O_TRUNC | O_CREAT, 0644);
			else if (exec->cmd[exec->i - 1].token == APPEND)
				fd = open(exec->cmd[exec->i].cmd[0],
						O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (fd == -1)
				fail = 1;
			else if (exec->cmd[exec->i].token == OUT)
				close(fd);
		}
		exec->i++;
	}
	if (fail == 0)
		exec->fd_out = fd;
	else
	{
		exec->fd_out = -1;
		free(exec->tab_pid);
		exec_free(exec);
	}
}

void	dup2_manager(t_exec *exec, int tab_pipe[2][2])
{
	if (exec->i != 0 && exec->cmd[exec->i - 1].token == PIPE)
		dup2(tab_pipe[(exec->nb_fork - 1) % 2][0], 0);
	if (exec->cmd[exec->i].token == PIPE)
		dup2(tab_pipe[exec->nb_fork % 2][1], 1);
	if (((exec->cmd[exec->i].token == OUT
				&& (exec->i == 0 || exec->cmd[exec->i - 1].token == PIPE))
			|| (exec->i != 0 && exec->cmd[exec->i - 1].token == OUT))
		|| ((exec->cmd[exec->i].token == APPEND
				&& (exec->i == 0 || exec->cmd[exec->i - 1].token == PIPE))
			|| (exec->i != 0 && exec->cmd[exec->i - 1].token == APPEND)))
	{
		open_file(exec);
		dup2(exec->fd_out, 1);
	}
}

void	inside_fork(t_exec *exec, char **envp, int tab_pipe[2][2])
{
	int	ret;
	int	i;

	i = exec->i;
	dup2_manager(exec, tab_pipe);
	close_pipe(tab_pipe);
	ret = execve(exec->cmd[i].cmd[0], exec->cmd[i].cmd, envp);
	if (ret == -1)
		exec_free(exec);
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

void	exec_cmd(t_exec *exec, char **envp, t_env_list **list_var, int tab_pipe[2][2])
{
	if (ft_strcmp(exec->cmd[exec->i].cmd[0], "echo") == 0
		|| ft_strcmp(exec->cmd[exec->i].cmd[0], "cd") == 0
		|| ft_strcmp(exec->cmd[exec->i].cmd[0], "pwd") == 0
		|| ft_strcmp(exec->cmd[exec->i].cmd[0], "export") == 0
		|| ft_strcmp(exec->cmd[exec->i].cmd[0], "unset") == 0
		|| ft_strcmp(exec->cmd[exec->i].cmd[0], "env") == 0
		|| ft_strcmp(exec->cmd[exec->i].cmd[0], "exit") == 0)
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
		//incrementer le compter meme si redirection
	}
}
