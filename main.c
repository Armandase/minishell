#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_env_list	*list_var;
	char		*line;
	char		*prompt;
	t_cmd		*cmd;

	(void)ac;
	(void)av;
	cmd = NULL;
	list_var = NULL;
	list_var = create_env_list(envp);
	signal(SIGINT, exit_signals);
	while (1)
	{
		prompt = create_prompt();
		line = readline(prompt);
		free(prompt);
		if (line == NULL)
			exit_shell(list_var);	
		cmd = parsing(line);
		execution(cmd, envp, list_var);
		if (line && *line)
			add_history(line);
		free(line);
	}
	return (0);
}
