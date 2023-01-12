#include "execution.h"

void	exit_signals(int signum)
{
	if (signum == SIGINT)
		ft_printf("SIGSTOP\n");
	exit(1);
}
