/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:01:23 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/06 16:12:25 by ulayus           ###   ########.fr       */
/*   Updated: 2023/02/05 18:56:31 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../builtins/builtins.h"
# include "../parsing/parsing.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# define PROMPT 0
# define HERE_DOC 1
# define NO_EXEC 0
# define DEFAULT 1

void	execution(t_cmd *cmd, char **envp, t_env_list **list_var);
void	exec_cmd(t_exec *exec, t_cmd *cmd, int tab_pipe[2][2]);
void	get_cmd_path(char **cmd, char **envp);
void	print_error(char *error, int exit_code, t_cmd *cmd);
void	builtins_selection(t_cmd *cmd, t_exec *exec, int tab_pipe[2][2]);
void	exit_shell(t_env_list **list_var, char **envp);
char	*create_prompt(void);
void	handle_sigint(int signum);
void	handle_sigint_exec(int signum);
void	handle_sigquit(int signum);
void	create_check_pipe(void);
void	open_pipe(int tab_pipe[2][2], int i);
void	close_pipe(int tab_pipe[2][2]);
void	fail_on_open(t_exec *exec, t_cmd *cmd, int pipe_tab[2][2]);
void	exec_free(t_exec *exec, t_cmd *cmd, int exit_code);
void	redirection_offset(t_cmd **cmd);
int		heredoc(t_cmd *cmd);
void	open_file(t_exec *exec, t_cmd *cmd, int check, int pipe_tab[2][2]);
void	free_list_var(t_env_list **list_var, char **envp);
void	free_stack(t_cmd *cmd);
bool	get_heredoc(t_cmd *cmd, t_env_list **list_var, char **envp);
void	free_struct(t_cmd *cmd);
void	close_heredoc(void);
void	exec_builtins(t_cmd *cmd, int *ret, int tab_pipe[2][2], t_exec *exec);
int		verif_args(t_cmd *cmd, int check);

#endif
