#include "minishell.h"

/*void	printf_all(t_cmd *cmd)
{
	int	i;
	int j;

	i = 0;
	while (cmd[i].cmd != NULL)
	{
		j = 0;
		while (cmd[i].cmd[j] != NULL)
		{
			printf("token %d; cmd :%s\n", i, cmd[i].cmd[j]);
			j++;
		}
		i++;
	}
}
*/
t_sh_state	g_sh_state;

int	main(int ac, char **av, char **envp)
{
	t_env_list	*list_var;
	char		*line;
	char		*prompt;
	t_cmd		*cmd;

	(void)ac;
	(void)av;
	cmd = NULL;
	list_var = create_env_list(envp);
	signal(SIGINT, handle_sigint);
	while (1)
	{
		g_sh_state.state = PROMPT;
		prompt = create_prompt();
		line = readline(prompt);
		envp = env_export(list_var);
		free(prompt);
		if (line == NULL)
			exit_shell(&list_var, envp);
		if (ft_strlen(line) != 0)
		{
			cmd = parsing(line);
			if (cmd != NULL)
				execution(cmd, envp, &list_var);
		}
		if (line && *line)
			add_history(line);
		if (line)
			free(line);
		if (envp)
			ft_free_strs(envp);
	}
	return (0);
}
