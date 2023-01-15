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
	//const char	reset = 127;

	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		ft_printf("\n");
		rl_on_new_line();
		//write(0, &reset, 1);
	}
}
