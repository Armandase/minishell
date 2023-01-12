#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"
# include "struct.h"
# include "unistd.h"

t_env_list	*create_env_list(char **envp);
void		main_env(char **args, t_env_list *list_var);
void		main_pwd(void);
void		*main_export(char **args, t_env_list *list_var);
void		*main_unset(char *arg_name, t_env_list **list_var);

#endif
