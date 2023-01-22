#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# define PROMPT 0
# define HERE_DOC 1

typedef struct s_sh_state
{
	int		state;
	bool	check_signal;
}			t_sh_state;

void	execution(t_cmd *cmd, char **envp, t_env_list **list_var);
void	exec_cmd(t_exec *exec, t_cmd *cmd, int tab_pipe[2][2]);
void	get_cmd_path(char **cmd, char **envp);
void	print_error(char *error, int exit_code, t_cmd *cmd);
void	builtins_selection(t_cmd *cmd, t_exec *exec);
void	exit_shell(t_env_list **list_var, char **envp);
char	*create_prompt(void);
void	handle_sigint(int signum);
void	open_pipe(int tab_pipe[2][2], int i);
void	close_pipe(int tab_pipe[2][2]);
void	exec_free(t_exec *exec, t_cmd *cmd, int exit_code);
void	redirection_offset(t_cmd **cmd);
int		heredoc(t_cmd *cmd);
void	open_input_file(t_exec *exec, t_cmd *cmd, int check);

#endif
