#include "minishell.h"

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
	//signal(SIGQUIT, exit_shell);
	while (1)
	{
		prompt = create_prompt();
		line = readline(prompt);
		free(prompt);
		cmd = parsing(line);
		execution(cmd, envp, list_var);
		if (line && *line)
			add_history(line);
		free(line);
	}
	return (0);
}
