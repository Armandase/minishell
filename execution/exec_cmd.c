#include "execution.h"

void	open_input_file(t_exec *exec, t_cmd *cmd, int check)
{
	int		in;
	int		out;
	int		fail;
	t_cmd	*cpy;

	cpy = cmd;
	fail = 0;
	in = -2;
	out = -2;
	while (cpy->next != NULL && cpy->token != CMD && cpy->token != BUILTINS)
	{
		if (fail == 0)
		{
			if (cpy->token == IN)
			{
				cpy = cpy->next;
				if (!cpy)
					return ;
				in = open(cpy->cmd[0], O_RDONLY);
				exec->fd_in = in;
				if (check != 1)
					dup2(exec->fd_in, 0);
				else if (check == 1 && in != -1 && in != -2)
					close(in);
			}
			else if (cpy->token == HEREDOC)
			{
				cpy = cpy->next;
				if (!cpy)
					return ;
				in = heredoc(cpy);
				exec->fd_in = in;
				if (check != 1)
					dup2(exec->fd_in, 0);
				else if (check == 1 && in != -1 && in != -2)
					close(in);
			}
			else if (cpy->token == OUT)
			{
				cpy = cpy->next;
				if (!cpy)
					return ;
				out = open(cpy->cmd[0],
						O_WRONLY | O_TRUNC | O_CREAT, 0644);
				exec->fd_out = out;
				if (check != 1)
					dup2(exec->fd_out, 1);
				else if (check == 1 && out != -1 && out != -2)
					close(out);
			}
			else if (cpy->token == APPEND)
			{
				cpy = cpy->next;
				if (!cpy)
					return ;
				out = open(cpy->cmd[0],
						O_WRONLY | O_APPEND | O_CREAT, 0644);
				exec->fd_out = out;
				if (check != 1)
					dup2(exec->fd_out, 1);
				else if (check == 1 && out != -1 && out != -2)
					close(out);
			}
			if (in == -1 || out == -1)
				fail = 1;
			else if (cpy->next && (cpy->next->token == IN || cpy->next->token == HEREDOC))
				close(in);
			else if (cpy->next && (cpy->next->token == OUT || cpy->next->token == APPEND))
				close(out);
		}
		cpy = cpy->next;
	}
	if (fail == 1)
	{
		if (exec->fd_in != -1)
			close(exec->fd_in);
		else if (exec->fd_out != 1)
			close(exec->fd_out);
		exec->fd_in = -1;
		exec->fd_out = -1;
		exec_free(exec, cmd, 1);
	}
}

void	dup2_manager(t_exec *exec, int tab_pipe[2][2], t_cmd *cmd)
{
	if (cmd->next && (cmd->token == FILES || cmd->token == CMD || cmd->token == 0 || cmd->token == BUILTINS))
		cmd = cmd->next;
	if (cmd->token == HEREDOC
		|| cmd->token == IN
		|| cmd->token == OUT
		|| cmd->token == APPEND)
		open_input_file(exec, cmd, 0);
	if (cmd->prev && (cmd->prev->token == FILES || cmd->prev->token == CMD || cmd->prev->token == 0 || cmd->prev->token == BUILTINS))
		cmd = cmd->prev;
	if (cmd->prev && cmd->prev->token == PIPE)
		dup2(tab_pipe[exec->nb_fork - 1 % 2][0], 0);
	while (cmd->next)
	{
		if (cmd->token == PIPE || cmd->token == 0)
			break ;
		cmd = cmd->next;
	}
	if (cmd && cmd->token == PIPE)
		dup2(tab_pipe[exec->nb_fork % 2][1], 1);
}

void	inside_fork(t_exec *exec, t_cmd *cmd, int tab_pipe[2][2])
{
	int	ret;

	ret = 0;
	dup2_manager(exec, tab_pipe, cmd);
	close_pipe(tab_pipe);
	if (cmd->token == CMD)
		ret = execve(cmd->cmd[0], cmd->cmd, exec->envp);
	else if (cmd->token == BUILTINS)
	{
		if (cmd->cmd && cmd->cmd[0] && (ft_strcmp(cmd->cmd[0], "echo") == 0))
			main_echo(cmd->cmd);
		else if (cmd->cmd && cmd->cmd[0] && (ft_strcmp(cmd->cmd[0], "pwd") == 0))
			main_pwd();
		else if (cmd->cmd && cmd->cmd[0] && (ft_strcmp(cmd->cmd[0], "export") == 0))
			main_export(cmd->cmd, exec->list_var);
		else if (cmd->cmd && cmd->cmd[0] && (ft_strcmp(cmd->cmd[0], "unset") == 0))
			main_unset(cmd->cmd, exec->list_var);
		else if (cmd->cmd && cmd->cmd[0] && (ft_strcmp(cmd->cmd[0], "env") == 0))
			main_env(cmd->cmd, *exec->list_var);
		else if (cmd->cmd && cmd->cmd[0] && (ft_strcmp(cmd->cmd[0], "cd") == 0))
			main_cd(cmd->cmd, exec->list_var);
		else if (cmd->cmd && cmd->cmd[0] && (ft_strcmp(cmd->cmd[0], "exit") == 0))
			main_exit(cmd, exec);
	}
	exec_free(exec, cmd, ret);
}

void	apply_execution(t_exec *exec, t_cmd *cmd, int tab_pipe[2][2])
{
	open_pipe(tab_pipe, exec->nb_fork);
	exec->tab_pid[exec->nb_fork] = fork();
	if (exec->tab_pid[exec->nb_fork] == -1)
		print_error("Fork error", 127, cmd);
	else if (exec->tab_pid[exec->nb_fork] == 0)
		inside_fork(exec, cmd, tab_pipe);
}

void	exec_cmd(t_exec *exec, t_cmd *cmd, int tab_pipe[2][2])
{
	if (cmd->cmd != NULL && cmd->token == CMD
		&& (ft_strcmp(cmd->cmd[0], "echo") == 0
			|| ft_strcmp(cmd->cmd[0], "pwd") == 0
			|| ft_strcmp(cmd->cmd[0], "export") == 0
			|| ft_strcmp(cmd->cmd[0], "unset") == 0
			|| ft_strcmp(cmd->cmd[0], "env") == 0
			|| ft_strcmp(cmd->cmd[0], "cd") == 0
			|| ft_strcmp(cmd->cmd[0], "exit") == 0))
		builtins_selection(cmd, exec);
	if (cmd->cmd && cmd->token == CMD && cmd->token != BUILTINS
		&& access(cmd->cmd[0], X_OK) != 0)
	{
		get_cmd_path(cmd->cmd, exec->envp);
		if (cmd->cmd[0] == NULL)
		{
			print_error("Error", 127, cmd);
			return ;
		}
	}
	apply_execution(exec, cmd, tab_pipe);
	exec->nb_fork++;
}
