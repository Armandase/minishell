#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

void	execution(t_cmd *cmd, char **envp, t_env_list *list_var);
void	exec_cmd(t_cmd *cmd, int i, char **envp, t_env_list *list_var);
void	get_cmd_path(char **cmd, char **envp);
void	print_error(char *error, int exit_code, t_cmd *cmd);
void	builtins_selection(t_cmd *cmd, t_env_list *list_var);
void	exit_shell(int signum);

#endif
