#include "../libft/libft.h"
#include "parsing.h"

static int	find_next_quote(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
		if (str[i] && str[i] == c)
			return (i);
	}
	return (-1);
}

static int	len_token(char *str, const char *delim, t_token *token)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			tmp = find_next_quote(&str[i], '\'');
			if (tmp == -1)
				return (0);
			i += tmp;
		}
		else if (str[i] == '\"')
		{
			tmp = find_next_quote(&str[i], '\"');
			if (tmp == -1)
				return (0);
			i += tmp;
		}
		j = 0;
		while (delim[j])
		{
			if (str[i] == delim[j])
			{
				if (delim[j] == '|')
					token->id = PIPE;
				else if (delim[j] == '<' && str[i + 1] && str[i + 1] == '<')
					token->id = HEREDOC;
				else if (delim[j] == '>' && str[i + 1] && str[i + 1] == '>')
					token->id = APPEND;
				else if (delim[j] == '<')
					token->id = IN;
				else if (delim[j] == '>')
					token->id = OUT;
				return (i);
			}
			j++;
		}
		i++;
	}
	return (i);
}

static int	check_delim(char c, const char *delim)
{
	int	i;

	i = 0;
	while (delim[i])
	{
		if (delim[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/****************************************/
/*Strtok be like sauf que :				*/
/*	separe en fonction des delimiteurs	*/
/*	sauf si entre quotes				*/
/*	return str coupé par le delimiteur	*/
/*	et le delimiteur qui l'a cut		*/
/****************************************/
t_token	*str_get_token(char *str, const char *delim)
{
	int			len;
	static char	*cpy = NULL;
	t_token		*token;

	len = 0;
	token = malloc(sizeof(t_token));
	token->id = 0;
	if (str != && ft_strlen(str) == 0)
		return (NULL);
	if (str != NULL)
		cpy = str;
	len = len_token(cpy, delim, token);
	if (len == 0)
	{
		token->line = NULL;
		return (token);
	}
	token->line = malloc(len + 1);
	token->line = ft_strncpy(token->line, cpy, len);
	token->line[len] = '\0';
	cpy += len;
	while (cpy && check_delim(*cpy, delim))
		cpy++;
	return (token);
}
