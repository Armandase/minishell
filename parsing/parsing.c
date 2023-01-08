#include "parsing.h"

void	get_cmd(cmd_t *cmd, char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	//recupere le premier token
	tmp = strtok_unquote(line, ">|<");
	//coupe le token en param : 1=cmd 2=arg_cmd 3=arg_cmd etc.. dernier=NULL
	cmd[i].cmd = split_token(tmp, ' ');
	i++;
	while (tmp != NULL)
	{
		free(tmp);
		tmp = strtok_unquote(NULL, ">|<");
		if (!tmp)
			break ;
		cmd[i].cmd = split_token(tmp, ' ');
		i++;
	}
	cmd[i].cmd = NULL;
}

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


void	parsing(char *line, char **envp)
{
	int		nb_token;
	cmd_t	*cmd;

	nb_token = number_token(line);
	cmd = malloc (sizeof(cmd_t) * (nb_token + 1));
	get_cmd(cmd, line);
	int	i = 0;
	int	j = 0;
	while (cmd[i].cmd != NULL)
	{
		j = 0;
		printf("command %d:\n", i);
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
