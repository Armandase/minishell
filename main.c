#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_env_list	*list_var;
	char		*line;
	t_cmd		*cmd;

	(void)ac;
	(void)av;
	cmd = NULL;
	list_var = NULL;
	list_var = create_env_list(envp);
	while (1)
	{
		line = readline("Minishell$ ");
		cmd = parsing(line);
		execution(cmd, envp, list_var);
		if (line && *line)
			add_history(line);
		free(line);
	}
	return (0);
}
