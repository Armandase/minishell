#include "execution.h"

extern t_sh_state	g_sh_state;

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
	prompt[i] = '$';
	prompt[i + 1] = ' ';
	return (prompt);
}

void	handle_sigint(int signum)
{
	(void)signum;
	//char	*prompt;

	//prompt = create_prompt();
	if (g_sh_state.state == PROMPT)
	{
		/*
		ft_printf("\n%s", prompt);
		rl_replace_line("", 0);
		free(prompt);
		*/
		rl_replace_line("", 0);
		ft_printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_sh_state.state == HERE_DOC)
		g_sh_state.check_signal = true;
}

void	handle_sigquit(int signum)
{
	(void)signum;
	ft_printf("Quit (core dumped)\n");
}
