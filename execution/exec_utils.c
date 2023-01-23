#include "execution.h"
#include <unistd.h>

void	free_list_var(t_env_list **list_var, char **envp)
{
	t_env_list	*head;
	t_env_list	*tmp;

	ft_free_strs(envp);
	head = *list_var;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		if (tmp)
		{
			free(tmp->name);
			free(tmp->value);
			free(tmp);
		}
	}
}

void	exec_free(t_exec *exec, t_cmd *cmd, int exit_code)
{
	int		j;
	t_cmd	*tmp;

	if (exit_code)
		print_error("Error", exit_code, NULL);
	if (cmd)
	{
		while (cmd->next != NULL)
		{
			j = 0;
			if (cmd->cmd)
			{
				while (cmd->cmd[j] != NULL)
				{
					free(cmd->cmd[j]);
					j++;
				}
			free(cmd->cmd);
			}
			tmp = cmd;
			cmd = cmd->next;
			free(tmp);
		}
		free(cmd);
	}
	if (exec && exec->tab_pid)
		free(exec->tab_pid);
	free_list_var(exec->list_var, exec->envp);
	exit(exit_code);
}

void	print_error(char *error, int exit_code, t_cmd *cmd)
{
	perror(error);
	(void)cmd;
	(void)exit_code;
}

int	builtins_check_pipe(t_cmd *cmd)
{
	while (cmd->prev != NULL)
		cmd = cmd->prev;
	while (cmd->next != NULL)
	{
		if (cmd->token == PIPE)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

void	builtins_without_redirect(t_cmd *cmd, t_exec *exec)
{
	int	exit_code;

	exit_code = 0;
	cmd->token = BUILTINS;
	if (cmd->next && (cmd->token == FILES || cmd->token == CMD || cmd->token == 0 || cmd->token == BUILTINS))
		cmd = cmd->next;
	if (cmd->token == HEREDOC
		|| cmd->token == IN
		|| cmd->token == OUT
		|| cmd->token == APPEND)
		open_input_file(exec, cmd, 1);
	if (cmd->prev && (cmd->prev->token == FILES || cmd->prev->token == CMD || cmd->prev->token == 0 || cmd->prev->token == BUILTINS))
		cmd = cmd->prev;
	if (cmd->cmd && cmd->cmd[0] && (ft_strcmp(cmd->cmd[0], "cd") == 0))
		exit_code = main_cd(cmd->cmd, exec->list_var);
	else if (cmd->cmd && cmd->cmd[0] && (ft_strcmp(cmd->cmd[0], "exit") == 0))
		main_exit(cmd, exec);
	else if (cmd->cmd && cmd->cmd[0] && (ft_strcmp(cmd->cmd[0], "export") == 0))
		exit_code = main_export(cmd->cmd, exec->list_var);
	else if (cmd->cmd && cmd->cmd[0] && (ft_strcmp(cmd->cmd[0], "unset") == 0))
		exit_code = main_unset(cmd->cmd, exec->list_var);
	search_replace_var("?", ft_itoa(exit_code), exec->list_var);
}

void	builtins_selection(t_cmd *cmd, t_exec *exec)
{
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		cmd->token = BUILTINS;
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		cmd->token = BUILTINS;
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		cmd->token = BUILTINS;
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
	{
		if (builtins_check_pipe(cmd))
			cmd->token = BUILTINS;
		else
			builtins_without_redirect(cmd, exec);
	}
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
	{
		if (builtins_check_pipe(cmd))
			cmd->token = BUILTINS;
		else
			builtins_without_redirect(cmd, exec);
	}
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
	{
		if (builtins_check_pipe(cmd))
			cmd->token = BUILTINS;
		else
			builtins_without_redirect(cmd, exec);
	}
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
	{
		if (builtins_check_pipe(cmd))
			cmd->token = BUILTINS;
		else
			builtins_without_redirect(cmd, exec);
	}
}

void	open_pipe(int tab_pipe[2][2], int i)
{
	close(tab_pipe[i % 2][1]);
	close(tab_pipe[i % 2][0]);
	pipe(tab_pipe[i % 2]);
}

void	close_pipe(int tab_pipe[2][2])
{
	close(tab_pipe[1][1]);
	close(tab_pipe[1][0]);
	close(tab_pipe[0][1]);
	close(tab_pipe[0][0]);
}

void	redirection_offset(t_cmd **cmd)
{
	if (*cmd)
		*cmd = (*cmd)->next;
	while ((*cmd)->next)
	{
		if ((*cmd)->token == CMD || (*cmd)->token == 0)
			break ;
		*cmd = (*cmd)->next;
	}
}
