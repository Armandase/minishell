#include "../libft/libft.h"

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

int	len_token(char *str, const char *delim)
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
			{
				ft_putstr_fd("Missing a closing quote.\n", 2);
				return (0);
			}
			i += tmp;
		}
		else if (str[i] == '\"')
		{
			tmp = find_next_quote(&str[i], '\"');
			if (tmp == -1)
			{
				ft_putstr_fd("Missing a closing quote.\n", 2);
				return (0);
			}
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

int	check_delim(char c, const char *delim)
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

char	*strtok_unquote(char *str, const char *delim)
{
	int			len;
	static char	*cpy = NULL;
	char		*token;

	len = 0;
	if (str != NULL)
	{
		cpy = str;
		if (!cpy)
			return (NULL);
	}
	len = len_token(cpy, delim);
	if (len == 0)
		return (NULL);
	token = malloc(len + 1);
	token = ft_strncpy(token, cpy, len);
	token[len] = '\0';
	cpy += len;
	while (cpy && check_delim(*cpy, delim))
		cpy++;
	return (token);
}
