#include "execution.h"

char	*create_prompt(void)
{
	int		i;
	char	*prompt;

	prompt = ft_calloc(1024, 1);
	if (prompt == NULL)
		return (NULL);
	getcwd(prompt, 1024);
	i = 0;
	while (prompt[i])
		i++;
	prompt[i] = ' ';
	return (prompt);
}

void	exit_signals(int signum)
{
	char	*prompt;

	prompt = create_prompt();
	if (signum == SIGINT)
	{
		ft_printf("\n%s", prompt);
		free(prompt);
	}
}
