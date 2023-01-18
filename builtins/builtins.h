#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"
# include "struct.h"
# include <unistd.h>
# define PWD 0
# define OLDPWD 1

t_env_list	*create_env_list(char **envp);
void		main_env(char **args, t_env_list *list_var);
void		main_pwd(void);
void		*main_export(char **args, t_env_list **list_var);
void		*main_unset(char **args, t_env_list **list_var);
void		*main_cd(char **args, t_env_list **list_var);
void		main_echo(char **args);
void		main_exit(char **args, t_env_list **list_var);
void		print_args_ascii(t_env_list *list_var, size_t size);
size_t		env_list_size(t_env_list *list_var);
char		**env_export(t_env_list *list_var);
bool		search_var(char *var, t_env_list **list_var);

#endif
