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

static int	len_token(char *str, const char *delim)
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
			if (tmp == -1){}
				//dire que quote n'est pas ferme dans la ligne
			i += tmp;
		}
		else if (str[i] == '\"')
		{
			tmp = find_next_quote(&str[i], '\"');
			if (tmp == -1){}
				//dire que quote n'est pas ferme dans la ligne
			i += tmp;
		}
		j = 0;
		while (delim[j])
		{
			if (str[i] == delim[j])
				return (i);
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

t_token	*str_get_token(char *str, const char *delim)
{
	int			len;
	static char	*cpy = NULL;
	char		*tmp;
	t_token		*token;

	len = 0;
	token = malloc(sizeof(t_token));
	if (str != NULL)
	{
		cpy = str;
		if (!cpy)
			return (NULL);
	}
	len = len_token(cpy, delim);
	if (len == 0)
	{
		token->line = NULL;
		return (token);
	}
	tmp = malloc(len + 1);
	tmp = ft_strncpy(tmp, cpy, len);
	tmp[len] = '\0';
	cpy += len;
	while (cpy && check_delim(*cpy, delim))
		cpy++;
	token->line = ft_strdup(tmp);
	free(tmp);
	token->id = 1; 
	return (token);
}
