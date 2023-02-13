/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 10:31:44 by ulayus            #+#    #+#             */
/*   Updated: 2023/02/11 15:23:11 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution/execution.h"

t_sh_state	g_sh_state;

void	start_shell(char *line, t_cmd *cmd, t_env_list *list_var, char **envp)
{
	if (ft_strlen(line) != 0)
	{
		cmd = parsing(line, list_var);
		if (cmd != NULL)
		{
			signal(SIGINT, handle_sigint_exec);
			signal(SIGQUIT, handle_sigquit);
			execution(cmd, envp, &list_var);
			g_sh_state.state = PROMPT;
		}
	}
	if (line && *line)
		add_history(line);
	if (line)
		free(line);
	if (envp)
		ft_free_strs(envp);
}

int	main(int ac, char **av, char **envp)
{
	t_env_list	*list_var;
	char		*line;
	t_cmd		*cmd;
	char		*prompt;

	(void)av;
	if (ac != 1)
		return (1);
	cmd = NULL;
	list_var = create_env_list(envp);
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		g_sh_state.check_signal = false;
		g_sh_state.state = PROMPT;
		prompt = create_prompt();
		line = readline(prompt);
		envp = env_export(list_var);
		free(prompt);
		if (line == NULL)
			exit_shell(&list_var, envp);
		start_shell(line, cmd, list_var, envp);
	}
	return (0);
}
