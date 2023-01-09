#include "parsing.h"

void	free_cmd(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i].cmd[0] != NULL)
	{
		j = 0;
		while (cmd[i].cmd[j] != NULL)
		{
			free(cmd[i].cmd[j]);
			j++;
		}
		free(cmd[i].cmd);
		i++;
	}
	free(cmd);
}
