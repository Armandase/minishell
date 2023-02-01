/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:17:44 by ulayus            #+#    #+#             */
/*   Updated: 2023/01/31 13:03:02 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	search_replace_pwd(char *pwd, int flag, t_env_list **list_var)
{
	t_env_list	*tmp;

	tmp = *list_var;
	while (tmp->next)
	{
		if (flag == PWD)
		{
			if (ft_strcmp("PWD", tmp->name) == false)
			{
				free(tmp->value);
				tmp->value = pwd;
			}
		}
		else if (flag == OLDPWD)
		{
			if (ft_strcmp("OLDPWD", tmp->name) == false)
			{
				free(tmp->value);
				tmp->value = pwd;
			}
		}
		tmp = tmp->next;
	}
}

char	*get_current_pwd(t_env_list **list_var)
{
	t_env_list	*tmp;

	tmp = *list_var;
	while (tmp->next)
	{
		if (ft_strcmp("PWD", tmp->name) == false)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	print_error(char *dir)
{
	ft_putstr_fd("minishell: cd: ", 2);
	write(2, dir, ft_strlen(dir));
	ft_putstr_fd(": No such file or directory\n", 2);
}

int	main_cd(char **args, t_env_list **list_var)
{
	char	*old_pwd;
	char	*pwd;

	if (ft_strlen_2d((const char **)args) > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	old_pwd = ft_calloc(4096, sizeof(char));
	if (old_pwd == NULL)
		return (12);
	old_pwd = getcwd(old_pwd, 4096);
	if (args[1] && chdir(args[1]))
	{
		print_error(args[1]);
		free(old_pwd);
		return (1);
	}
	pwd = ft_calloc(4096, sizeof(char));
	if (pwd == NULL)
	{
		free(old_pwd);
		return (12);
	}
	getcwd(pwd, 4096);
	search_replace_pwd(old_pwd, OLDPWD, list_var);
	search_replace_pwd(pwd, PWD, list_var);
	return (0);
}
