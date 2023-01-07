#include "parsing.h"
#include <stdlib.h>

int	number_cmd(char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strtok(line, ">|<");
	i++;
	while (tmp != NULL)
	{
		free(tmp);
		tmp = ft_strtok(NULL, ">|<");
		i++;
	}
	return (i);
}

char	**token_in_line(cmd_t *cmd, char *line)
{
	int		i;
	char	*tmp;
	char	**strs;

	i = 0;
	strs = malloc(sizeof(char *) * number_cmd(line));
	tmp = ft_strtok(line, ">|<");
	strs[i] = ft_strdup(tmp);
	i++;
	while (tmp != NULL)
	{
		free(tmp);
		tmp = ft_strtok(NULL, ">|<");
		i++;
		strs[i] = ft_strdup(tmp);
	}
	strs[i] = NULL;
	return (strs);
}

void	get_cmd(cmd_t *cmd, char *line)
{
	char	**strs;

	strs = token_in_line(cmd, line);
	find_quote_in_token(strs);
}


void	parsing(char *line, char **envp)
{
	int		nb_cmd;
	cmd_t	*cmd;
	int		i;

	nb_cmd = number_cmd(line);
	cmd = malloc (sizeof(cmd_t) * nb_cmd);
	get_cmd(cmd, line);
}
