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

/********************************************************/
/*	Parsing:											*/
/*	  separe la ligne avec delimiteurs(become tokens)	*/
/*	  split ces tokens par les espaces (cmd & arg)		*/
/********************************************************/
t_cmd	*parsing(char *line, char **envp)
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
		ft_printf("command %d, token: %d\n", i, cmd[i].token);
		while(cmd[i].cmd[j] != NULL)
		{
			ft_printf("\t->arg %d: %s\n", j, cmd[i].cmd[j]);
			j++;
		}
		i++;
	}
	return (cmd);
}
