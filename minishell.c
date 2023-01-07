#include "minishell.h"
#include <readline/history.h>

int	main(int ac, char **av, char **envp)
{
	char	*line;

	(void)ac;
	(void)av;
	(void)envp;
	while (1)
	{
		line = readline("Minishell$ ");
		if (line && *line)
			add_history(line);
		free(line);
	}
	return (0);
}
