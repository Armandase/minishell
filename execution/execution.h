#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"
# include <sys/types.h>
# include <sys/wait.h>

void	execution(t_cmd *cmd, char **envp);
void	exec_cmd(t_cmd *cmd, int i, char **envp);
void	get_cmd_path(char **cmd, char **envp);

#endif
