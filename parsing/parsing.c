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
	*exit = 0;
	while (cmd[i].cmd != NULL)
	{
		cmd[i].exit = exit;
		i++;
	}
}

void	begin_offset(t_cmd *cmd, char *line)
{
	if (line[0] && line[0] == '<' && line[1] && line[1] == '<')
		cmd[0].token = HEREDOC;
	else if (line[0] && line[0] == '>' && line[1] && line[1] == '>')
		cmd[0].token = APPEND;
	else if (line[0] && line[0] == '>')
		cmd[0].token = OUT;
	else if (line[0] && line[0] == '<')
		cmd[0].token = IN;
	cmd[0].cmd = malloc(sizeof(char **) * 2);
	cmd[0].cmd[0] = malloc(sizeof(char *) * 2);
	cmd[0].cmd[0][0] = FLAG;
	cmd[0].cmd[0][1] = '\0';
	cmd[0].cmd[1] = NULL;
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
	if (line[0] && (line[0] == '<' || line[0] == '>'))
	{
		begin_offset(cmd, line);
		i++;
	}
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

int	check_char(char c)
{
	if (c == '|'
		|| c == '>'
		|| c == '<')
		return (1);
	else
		return (0);
}

int	first_token_offset(char *line)
{
	if (line[0]
		&& (line[0] == '>' || line[0] == '<'))
		return (1);
	else
		return (0);
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
	if ((check_char(current_line[0]) == 1 && (ft_strlen(current_line) == 1 || current_line[0] == '|'))
		|| check_char(current_line[ft_strlen(current_line) - 1]) == 1)
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (NULL);
	}
	nb_token = number_token(current_line);
	cmd = malloc (sizeof(t_cmd) * (nb_token + first_token_offset(current_line) + 1));
	get_cmd(cmd, current_line);
	free(current_line);
	return (cmd);
}
