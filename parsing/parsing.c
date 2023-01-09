#include "parsing.h"
#include <stdlib.h>

int	number_token(char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = strtok_unquote(line, ">|<");
	i++;
	while (tmp != NULL)
	{
		free(tmp);
		tmp = strtok_unquote(NULL, ">|<");
		i++;
	}
	return (i);
}

void	get_cmd(t_cmd *cmd, char *line)
{
	int		i;
	t_token	*token;

	i = 0;
	token = str_get_token(line, ">|<");
	cmd[i].cmd = split_token(token->line, ' ');
	cmd[i].token = token->id;
	i++;
	while (token->line != NULL)
	{
		free(token->line);
		free(token);
		token = str_get_token(NULL, ">|<");
		if (token->line == NULL)
			break ;
		cmd[i].cmd = split_token(token->line, ' ');
		cmd[i].token = token->id;
		i++;
	}
	free(token);
	cmd[i].cmd = NULL;
}

void	parsing(char *line, char **envp)
{
	int		nb_token;
	t_cmd	*cmd;

	nb_token = number_token(line);
	cmd = malloc (sizeof(t_cmd) * (nb_token + 1));
	get_cmd(cmd, line);
	int	i = 0;
	int	j = 0;
	while (cmd[i].cmd != NULL)
	{
		j = 0;
		printf("command %d, token: %d\n", i, cmd[i].token);
		while(cmd[i].cmd[j] != NULL)
		{
			printf("\t->arg %d: %s\n", j, cmd[i].cmd[j]);
			j++;
		}
		i++;
	}
	//free_cmd(cmd);
	(void)envp;
}
