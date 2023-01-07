#include "minishell.h"
#include <readline/history.h>

int	main(int ac, char **av, char **envp)
{
	char	*line;

	(void)ac;
	(void)av;
	while (1)
	{
		line = readline("Minishell$ ");
		parsing(line, envp);
		if (line && *line)
			add_history(line);
		free(line);
	}
	return (0);
}
