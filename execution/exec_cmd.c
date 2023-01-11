#include "execution.h"
#include <stdlib.h>

void	apply_execution(t_cmd *cmd, int i, char **envp)
{
	int	pid;
	int	status;

	//if (i != 0 && cmd[i - 1])
	pid = fork();
	status = 0;
	if (pid == -1)
	{
		perror("Fork error.");
		*(cmd[i].exit) = 127;
	}
	if (pid == 0)
	{
		execve(cmd[i].cmd[0], cmd[i].cmd, envp);
		perror("Execve error.");
		*(cmd[i].exit) = 127;
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		*cmd[i].exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*cmd[i].exit = WTERMSIG(status);
}

void	exec_cmd(t_cmd *cmd, int i, char **envp)
{
	if (ft_strncmp(cmd[i].cmd[0], "echo", 4) == 0
		|| ft_strncmp(cmd[i].cmd[0], "cd", 2) == 0
		|| ft_strncmp(cmd[i].cmd[0], "pwd", 3) == 0
		|| ft_strncmp(cmd[i].cmd[0], "export", 6) == 0
		|| ft_strncmp(cmd[i].cmd[0], "unset", 5) == 0
		|| ft_strncmp(cmd[i].cmd[0], "env", 3) == 0
		|| ft_strncmp(cmd[i].cmd[0], "exit", 4) == 0)
		ft_printf("builtins in progress\n");
	else
	{
		if (access(cmd[i].cmd[0], X_OK) != 0)
		{
			get_cmd_path(&cmd[i].cmd[0], envp);
			if (cmd[i].cmd[0] == NULL)
			{
				ft_printf("Command not found.\n");
				*(cmd[i].exit) = 127;
				return ;
			}
		}
		apply_execution(cmd, i, envp);
	}
}
