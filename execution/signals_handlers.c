/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:58:22 by adamiens          #+#    #+#             */
/*   Updated: 2023/01/30 12:53:47 by ulayus           ###   ########.fr       */
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
	if (g_sh_state.state == PROMPT)
	{
		rl_replace_line("", 0);
		ft_printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_sh_state.state == HERE_DOC)
		g_sh_state.check_signal = true;
}

void	handle_sigint_exec(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	ft_printf("\n");
	rl_on_new_line();
}

void	handle_sigquit(int signum)
{
	(void)signum;
	ft_printf("Quit (core dumped)\n");
}
