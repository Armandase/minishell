#include "execution.h"

void	waiting_end(t_exec	*exec)
{
	int	wstatus;
	int	exit_code;
	int	i;

	i = 0;
	exit_code = -1;
	while (i < exec->nb_fork)
	{
		waitpid(exec->tab_pid[i], &wstatus, 0);
		if (WIFEXITED(wstatus))
			exit_code = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
			exit_code = WTERMSIG(wstatus);
		i++;
	}
	if (exit_code != -1 && g_sh_state.exit_code != 130)
		g_sh_state.exit_code = exit_code;
}

void	free_struct(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	while (cmd->prev != NULL)
		cmd = cmd->prev;
	while (cmd != NULL)
	{
		i = 0;
		if (cmd->cmd)
		{
			while (cmd->cmd[i] != NULL)
			{
				free(cmd->cmd[i]);
				i++;
			}
			free(cmd->cmd);
		}
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

int	tab_pid_len(t_cmd	*cmd)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (cmd->next != NULL)
	{
		if (cmd->token == CMD)
			ret++;
		i++;
		cmd = cmd->next;
	}
	ret += 2;
	return (ret);
}

void	check_nb_heredoc(t_cmd *cmd, t_env_list **list_var, char **envp)
{
	t_cmd	*cpy;
	int		i;

	i = 0;
	cpy = cmd;
	while (cpy->next)
	{
		if (cpy->token == HEREDOC)
			i++;
		cpy = cpy->next;
	}
	if (i > 16)
	{
		ft_putstr_fd("Maximum here-document count exceeded.\n", 2);
		free_struct(cmd);
		free_list_var(list_var, envp);
		exit(2);
	}
}

void	get_heredoc(t_cmd *cmd, t_env_list **list_var, char **envp)
{
	t_cmd	*cpy;
	int		i;

	i = 0;
	cpy = cmd;
	check_nb_heredoc(cmd, list_var, envp);
	while (i < 16)
	{
		g_sh_state.pipe_heredoc[i] = 1;
		i++;
	}
	i = 0;
	while (cpy->next)
	{
		if (cpy->token == HEREDOC && cpy->next)
		{
			g_sh_state.state = HEREDOC;
			cpy = cpy->next;
			g_sh_state.pipe_heredoc[i] = heredoc(cpy);
			i++;
		}
		else
			cpy = cpy->next;
	}
}

void	execution(t_cmd *cmd, char **envp, t_env_list **list_var)
{
	t_exec	exec;
	int		tab_pipe[2][2];

	get_heredoc(cmd, list_var, envp);
	pipe(tab_pipe[0]);
	pipe(tab_pipe[1]);
	exec.nb_fork = 0;
	exec.envp = envp;
	exec.list_var = list_var;
	exec.fd_out = -2;
	exec.fd_in = -2;
	exec.tab_pid = ft_calloc(sizeof(int), tab_pid_len(cmd));
	while (cmd->next != NULL)
	{
		exec_cmd(&exec, cmd, tab_pipe);
		redirection_offset(&cmd);
	}
	close_pipe(tab_pipe);
	waiting_end(&exec);
	while (cmd->prev != NULL)
		cmd = cmd->prev;
	free_struct(cmd);
	free(exec.tab_pid);
}
