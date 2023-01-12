#include "execution.h"
#include <stdlib.h>
#include <unistd.h>

void	inside_fork(t_cmd *cmd, int i, char **envp, int tab_pipe[2])
{
	if (i != 0 && cmd[i - 1].token == PIPE)
		dup2(cmd[i - 1].fd_out, 0);
	if (cmd[i].token == PIPE)
		dup2(tab_pipe[1], 1);
	close(tab_pipe[0]);
	close(tab_pipe[1]);
	execve(cmd[i].cmd[0], cmd[i].cmd, envp);
	print_error("Execve error", 127, cmd);
	exit(127);
}

void	apply_execution(t_cmd *cmd, int i, char **envp)
{
	int	pid;
	int	status;
	int	tab_pipe[2];

	pipe(tab_pipe);
	pid = fork();
	status = 0;
	if (pid == -1)
		print_error("Fork error", 127, cmd);
	else if (pid == 0)
		inside_fork(cmd, i, envp, tab_pipe);
	if (i != 0 && cmd[i - 1].token == PIPE)
		dup2(tab_pipe[1], 1);
	waitpid(pid, &status, 0);
	if (cmd[i].token == PIPE)
		cmd[i].fd_out = tab_pipe[0];
	if (WIFEXITED(status))
		*cmd[i].exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*cmd[i].exit = WTERMSIG(status);
}

void	exec_cmd(t_cmd *cmd, int i, char **envp, t_env_list *list_var)
{
	if (ft_strncmp(cmd[i].cmd[0], "echo", 4) == 0
		|| ft_strncmp(cmd[i].cmd[0], "cd", 2) == 0
		|| ft_strncmp(cmd[i].cmd[0], "pwd", 3) == 0
		|| ft_strncmp(cmd[i].cmd[0], "export", 6) == 0
		|| ft_strncmp(cmd[i].cmd[0], "unset", 5) == 0
		|| ft_strncmp(cmd[i].cmd[0], "env", 3) == 0
		|| ft_strncmp(cmd[i].cmd[0], "exit", 4) == 0)
		builtins_selection(&cmd[i], list_var);
	else
	{
		if (access(cmd[i].cmd[0], X_OK) != 0)
		{
			get_cmd_path(&cmd[i].cmd[0], envp);
			if (cmd[i].cmd[0] == NULL)
			{
				print_error("Command not found", 127, cmd);
				return ;
			}
		}
		apply_execution(cmd, i, envp);
	}
}
