/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:20:09 by ulayus            #+#    #+#             */
/*   Updated: 2023/02/13 13:12:48 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	free_exec(t_exec *exec)
{
	t_env_list	*env_tmp;

	while (*exec->list_var)
	{
		env_tmp = *exec->list_var;
		*exec->list_var = (*exec->list_var)->next;
		free(env_tmp->name);
		free(env_tmp->value);
		free(env_tmp);
		env_tmp = NULL;
	}
	if (exec->tab_pid != NULL)
		free(exec->tab_pid);
	if (exec->envp)
		ft_free_strs(exec->envp);
}

static void	free_cmd(t_cmd *cmd)
{
	t_cmd	*cmd_tmp;

	while (cmd->prev != NULL)
		cmd = cmd->prev;
	while (cmd != NULL)
	{
		cmd_tmp = cmd;
		cmd = cmd->next;
		ft_free_strs(cmd_tmp->cmd);
		free(cmd_tmp);
	}
}

static bool	check_format_code(const char *value)
{
	char	*nb_s;

	if (value[0] && ft_isdigit(value[0]) == false
		&& value[0] != '-' && value[0] != '+')
		return (false);
	nb_s = ft_lltoa(ft_atoll(value));
	if (value[0] != '+' && ft_strcmp(nb_s, value))
	{
		free(nb_s);
		return (false);
	}
	free(nb_s);
	return (true);
}

static int	check_multiple_args(const char **values, long long *exit_code)
{
	int	i;

	i = 0;
	while (values[i])
	{
		if (check_format_code(values[i]) == false)
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			*exit_code = 2;
			return (BREAK);
		}
		i++;
	}
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	return (1);
}

int	main_exit(t_cmd *cmd, t_exec *exec)
{
	long long	exit_code;
	const char	**values = (const char **)cmd->cmd;

	exit_code = 0;
	if (ft_strlen_2d(values) == 1)
		exit_code = g_sh_state.exit_code;
	else if (ft_strlen_2d(values) == 2)
	{
		exit_code = ft_atoll(values[1]);
		if (check_format_code(values[1]) == false)
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			exit_code = 2;
		}
	}
	else if (ft_strlen_2d(values) > 2)
		if (check_multiple_args(values, &exit_code) != BREAK)
			return (1);
	free_exec(exec);
	free_cmd(cmd);
	ft_printf("exit\n");
	exit(exit_code % 256);
}
