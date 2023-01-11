#include "execution.h"
#include <unistd.h>

void	exec_cmd(t_cmd *cmd, int i)
{
	if (ft_strcmp(cmd[i].cmd[0], "echo") == 0
		|| ft_strcmp(cmd[i].cmd[0], "cd") == 0
		|| ft_strcmp(cmd[i].cmd[0], "pwd") == 0
		|| ft_strcmp(cmd[i].cmd[0], "export") == 0
		|| ft_strcmp(cmd[i].cmd[0], "unset") == 0
		|| ft_strcmp(cmd[i].cmd[0], "env") == 0
		|| ft_strcmp(cmd[i].cmd[0], "exit") == 0)
		//builtins exec call
		ft_printf("builtins in progress");
	else
	{
		if (acces(cmd[i].cmd[0], X_OK) == 0)
			break ;
		mc
	}

}
