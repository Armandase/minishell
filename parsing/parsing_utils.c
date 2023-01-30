/********************************************************/
/*	Create a node for store a token value				*/
/*******************************************************/

#include "parsing.h"

void	begin_offset(t_cmd **cmd, char *line)
{
	*cmd = list_new(NULL, NULL);
	if (line[0] && line[0] == '<' && line[1] && line[1] == '<')
		(*cmd)->token = HEREDOC;
	else if (line[0] && line[0] == '>' && line[1] && line[1] == '>')
		(*cmd)->token = APPEND;
	else if (line[0] && line[0] == '>')
		(*cmd)->token = OUT;
	else if (line[0] && line[0] == '<')
		(*cmd)->token = IN;
}

/********************************************************/
/*À appliquer sur toutes les lignes:					*/
/*	separe la ligne par delimiteurs (>, >>, |, <<, <)	*/
/*	devient des tokens, stocker dans tab de cmd			*/
/*	assigne le delim qui a cut le token a cmd id		*/
/********************************************************/

void	create_node(t_cmd **cmd, t_token *token, t_env_list *list_var)
{
	(*cmd)->next = list_new(NULL, *cmd);
	(*cmd) = (*cmd)->next ;
	(*cmd)->token = token->id;
	while (token->line != NULL)
	{
		if (token->line)
			free(token->line);
		free(token);
		token = str_get_token(NULL, ">|<");
		if (token->line == NULL)
			break ;
		(*cmd)->next = list_new(split_token(&token, list_var), (*cmd));
		(*cmd) = (*cmd)->next ;
		(*cmd)->next = list_new(NULL, (*cmd));
		(*cmd) = (*cmd)->next ;
		(*cmd)->token = token->id;
	}
	free(token);
}

t_cmd	*get_cmd(char *line, t_env_list *list_var)
{
	t_cmd	*cmd;
	t_token	*token;

	cmd = NULL;
	if (line[0] && (line[0] == '<' || line[0] == '>'))
	{
		begin_offset(&cmd, line);
		if (line[0] && line[1] && ((line[0] == '<' && line[1] == '<')
				|| (line[0] == '>' && line[1] == '>')))
			line += 2;
		else if (line[0] && (line[0] == '>' || line[0] == '<'))
			line++;
		token = str_get_token(line, ">|<");
		cmd->next = list_new(split_token(&token, list_var), cmd);
		cmd = cmd->next;
	}
	else
	{
		token = str_get_token(line, ">|<");
		cmd = list_new(split_token(&token, list_var), NULL);
	}
	create_node(&cmd, token, list_var);
	while (cmd->prev != NULL)
		cmd = cmd->prev;
	return (cmd);
}

/********************************************************/
/*	Check if there are some delim						*/
/*	at the beginning or the at end of the line			*/
/********************************************************/

int	skip_quote(char *str, int *i, char c)
{
	(*i)++;
	while (str[*i] && str[*i] != c)
		(*i)++;
	if (!str[*i])
		return (1);
	else
		return (0);
}

int	check_char(char *str)
{
	int		i;

	if (((str[0] == '>' || str[0] == '<') && ft_strlen(str) == 1)
		|| str[ft_strlen(str) - 1] == '>' || str[ft_strlen(str) - 1] == '<'
		|| (str[0] == '|' || str[ft_strlen(str) - 1] == '|'))
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			if (skip_quote(str, &i, str[i]))
				return (1);
		if ((str[i] == '<' && str[i + 1] && str[i + 1] == '|')
			|| (str[i] == '>' && str[i + 1] && str[i + 1] == '|')
			|| (str[i] == '<' && str[i + 1] && str[i + 1] == '>')
			|| (str[i] == '>' && str[i + 1] && str[i + 1] == '<')
			|| (str[i] == '|' && str[i + 1] && str[i + 1] == '<')
			|| (str[i] == '|' && str[i + 1] && str[i + 1] == '>')
			|| (str[i] == '|' && str[i + 1] && str[i + 1] == '|'))
			return (1);
		i++;
	}
	return (0);
}
