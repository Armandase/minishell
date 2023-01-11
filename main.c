#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	//t_env_list	*list_var;
	char	*line;
	t_cmd	*cmd;

	(void)ac;
	(void)av;
	cmd = NULL;
	while (1)
	{
		line = readline("Minishell$ ");
		cmd = parsing(line, envp);
		execution(cmd);
		if (line && *line)
			add_history(line);
		free(line);
	}
	/*
	list_var = NULL;
	list_var = create_env_list(envp);
	list_var = main_export(av[1], av[2], list_var);
	list_var = main_unset(av[1], list_var);
	main_env(list_var);
	*/
	return (0);
}