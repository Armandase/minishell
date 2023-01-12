#include "execution.h"

void	exit_shell(int signum)
{
	if (signum == SIGINT)
		ft_printf("SIGSTOP\n");
	exit(1);
}
