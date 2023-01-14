#include "parsing.h"
#include <stdlib.h>

/********************************************/
/*	Compte le nombre de delimiteur			*/
/*	sauf ceux entre quote					*/
/********************************************/

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

void	add_exit_addr(t_cmd *cmd)
{
	int	i;
	int	*exit;

	i = 0;
	exit = ft_calloc(1, sizeof(int));
	while (cmd[i].cmd != NULL)
	{
		cmd[i].exit = exit;
		i++;
	}
}

/********************************************************/
/*À appliquer sur toutes les lignes:					*/
/*	separe la ligne par delimiteurs (>, >>, |, <<, <)	*/	
/*	devient des tokens, stocker dans tab de cmd			*/		
/*	assigne le delim qui a cut le token a cmd id		*/
/********************************************************/

void	get_cmd(t_cmd *cmd, char *line)
{
	int		i;
	t_token	*token;

	i = 0;
	token = str_get_token(line, ">|<");
	cmd[i].cmd = split_token(token->line, ' ', &cmd[i]);
	cmd[i].token = token->id;
	i++;
	while (token->line != NULL)
	{
		free(token->line);
		free(token);
		token = str_get_token(NULL, ">|<");
		if (token->line == NULL)
			break ;
		cmd[i].cmd = split_token(token->line, ' ', &cmd[i]);
		cmd[i].token = token->id;
		i++;
	}
	free(token);
	cmd[i].cmd = NULL;
	add_exit_addr(cmd);
}

/********************************************************/
/*	Parsing:											*/
/*	  separe la ligne avec delimiteurs(become tokens)	*/
/*	  split ces tokens par les espaces (cmd & arg)		*/
/********************************************************/
t_cmd	*parsing(char *line)
{
	int		nb_token;
	t_cmd	*cmd;
	char	*current_line;

	current_line = ft_strtrim(line, " ");
	if (ft_strlen(current_line) == 0)
	{
		free(current_line);
		return (NULL);
	}
	nb_token = number_token(current_line);
	cmd = malloc (sizeof(t_cmd) * (nb_token + 1));
	get_cmd(cmd, current_line);
	free(current_line);
	return (cmd);
}
