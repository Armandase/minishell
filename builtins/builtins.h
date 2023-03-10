/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:18:07 by ulayus            #+#    #+#             */
/*   Updated: 2023/02/13 13:31:23 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"
# include "../struct.h"
# define DEF 0
# define INVALID 1
# define APND 2

enum	e_cd_macros
{
	PWD,
	OLDPWD,
	BREAK,
	ARGS_NB,
	NO_DIR
};

extern t_sh_state	g_sh_state;

t_env_list	*create_env_list(char **envp);
int			main_env(char **args, t_env_list *list_var);
int			main_pwd(void);
int			main_export(char **args, t_env_list **list_var);
int			main_unset(char **args, t_env_list **list_var);
int			main_cd(char **args, t_env_list **list_var);
int			main_echo(char **args);
int			main_exit(t_cmd *cmd, t_exec *exec);
void		print_args_ascii(t_env_list *list_var, size_t size);
size_t		env_list_size(t_env_list *list_var);
char		**env_export(t_env_list *list_var);
bool		check_name(char *name, int flag);
char		*export_value(char *str);
char		*export_name(char *str);
char		*search_send_var(char *var, t_env_list **list_var);
bool		search_var(char *var, t_env_list **list_var);
void		search_replace_var(char *name, char *value, t_env_list **list_var);
char		*ft_strjoin_space(char *s1, char const *s2);
int			append_value(char **str, t_env_list **list_var);
int			check_format(char *line, char *name, char *value, int flag);

#endif
