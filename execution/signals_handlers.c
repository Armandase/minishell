/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:58:22 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/05 19:03:37 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
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
	prompt[i] = '$';
	prompt[i + 1] = ' ';
	return (prompt);
}

void	handle_sigint(int signum)
{
	(void)signum;
	if (*(g_sh_state.state) == PROMPT)
	{
		rl_replace_line("", 0);
		ft_printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	g_sh_state.exit_code = 130;
}

void	create_check_pipe(void)
{
	static int	signal[2];
	int			*status;

	status = malloc(sizeof(int));
	status = PROMPT;
	g_sh_state.state = status;
	pipe(signal);
	g_sh_state.signal = signal;
	ft_putstr_fd("0", g_sh_state.signal[1]);
}

void	handle_sigint_exec(int signum)
{
	(void)signum;
	if (*(g_sh_state.state) == HERE_DOC)
		ft_putstr_fd("1", g_sh_state.signal[1]);
	else
	{
		rl_replace_line("", 0);
		ft_printf("\n");
		rl_on_new_line();
	}
	g_sh_state.exit_code = 130;
}
