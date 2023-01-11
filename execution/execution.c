#include "execution.h"

void	execution(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd[i].cmd != NULL)
	{
		if (cmd[i].token == PIPE || cmd[i].token == 0)
			exec_cmd(cmd, i);

		i++;
	}
}
