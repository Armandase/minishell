#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"
# include "struct.h"
# include "unistd.h"

void		main_env(t_env_list *list_var);
void		main_pwd(void);
t_env_list	*main_export(char *name, char *value, t_env_list *list_var);
t_env_list	*main_unset(char *arg_name, t_env_list *list_var);
t_env_list	*create_env_list(char **envp);

#endif
