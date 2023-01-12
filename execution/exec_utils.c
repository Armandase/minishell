#include "execution.h"

void	print_error(char *error, int exit_code, t_cmd *cmd)
{
	perror(error);
	*(cmd->exit) = exit_code;
}

void	builtins_selection(t_cmd *cmd, t_env_list *list_var)
{
	if (ft_strncmp(cmd->cmd[0], "echo", 4) == 0)
		ft_printf("in progress");
	else if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0)
		ft_printf("in progress");
	else if (ft_strncmp(cmd->cmd[0], "pwd", 3) == 0)
		main_pwd();
	else if (ft_strncmp(cmd->cmd[0], "export", 6) == 0)
		main_export(cmd->cmd, list_var);
	else if (ft_strncmp(cmd->cmd[0], "unset", 5) == 0)
		ft_printf("in progress");
		//main_unset(cmd->cmd, list_var);
	else if (ft_strncmp(cmd->cmd[0], "env", 3) == 0)
		main_env(cmd->cmd, list_var);
	else if (ft_strncmp(cmd->cmd[0], "exit", 4) == 0)
		ft_printf("in progress");
}
