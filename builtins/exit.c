#include "builtins.h"

void	main_exit(t_cmd *cmd, t_exec *exec)
{
	t_cmd		*cmd_tmp;
	t_env_list	*env_tmp;
	int			exit_code;

	exit_code = 0;
	if (ft_strlen_2d((const char **)cmd->cmd) > 1)
	{
		exit_code = ft_atoi(cmd->cmd[1]);
		if (cmd->cmd[1][0] && ft_isdigit(cmd->cmd[1][0]) == false)
		{
			ft_putstr_fd("exit: numeric argument required\n", 2);
			exit_code = 2;
		}
	}
	while (exit_code > 256)
		exit_code -= 256;
	while (*exec->list_var)
	{
		env_tmp = *exec->list_var;
		*exec->list_var = (*exec->list_var)->next;
		free(env_tmp->name);
		free(env_tmp->value);
		free(env_tmp);
	}
	if (exec->tab_pid != NULL)
		free(exec->tab_pid);
	if (exec->envp)
		ft_free_strs(exec->envp);
	while (cmd->prev != NULL)
		cmd = cmd->prev;
	while (cmd->next != NULL)
	{
		cmd_tmp = cmd;
		cmd = cmd->next;
		ft_free_strs(cmd_tmp->cmd);
		free(cmd_tmp);
	}
	ft_printf("exit\n");
	exit(exit_code);
}
