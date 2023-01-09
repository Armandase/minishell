#include "parsing.h"

static int	find_next_quote(const char *str, char c)
{
	int	i;
	
	i = 0;
	while (str[i] != '\0')
	{
		i++;
		if (str[i] == c)
			return (i);
	}
	return (-1);
}

static size_t	count_word(char const *s, char c)
{
	size_t	i;
	size_t	count;
	int		tmp;

	i = 0;
	count = 1;
	tmp = 0;
	while (s[i] == c && s[i])
		i++;
	if (i + 1 == ft_strlen(s) || i == ft_strlen(s))
		return (0);
	while (s[i])
	{
		if (s[i] == '\'')
		{
			i++;
			tmp = find_next_quote(&s[i], '\'');
			i += tmp;
		}	
		if (s[i] == '\"')
		{
			i++;
			tmp = find_next_quote(&s[i], '\"');
			i += tmp;
		}	
		if (s[i] == c)
		{
			while (s[i] == c)
				i++;
			if (!s[i])
				return (count);
			count++;
		}
		i++;
	}
	return (count);
}

static size_t	count_char(char const *s, char c, size_t i)
{
	size_t	count;
	int		tmp;

	count = 0;
	tmp = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			tmp = find_next_quote(&s[i], '\'');
			count += tmp;
		}
		if (s[i] == '\"')
		{
			tmp = find_next_quote(&s[i], '\"');
			count += tmp;
		}
		if (s[i] == c)
			break ;
		count++;
		i++;
	}
	return (count);
}

static size_t	ft_strccpy(const char *s, char *str, char c, size_t j)
{
	size_t	i;

	i = 0;
	while (s[j] == c && s[j])
		j++;
	while (s[j])
	{
		if (s[j] == c)
			break ;
		if (s[j] == '\'')
		{
			j++;
			while (s[j])
			{
				str[i] = s[j];
				i++;
				j++;
				if (s[j] == '\'')
				{
					j++;
					break ;
				}
			}
		}
		if (s[j] == c || !s[j])
			break ;
		if (s[j] == '\"')
		{
			j++;
			while (s[j])
			{
				str[i] = s[j];
				i++;
				j++;
				if (s[j] == '\"')
				{
					j++;
					break ;
				}
			}
		}
		if (s[j] == c || !s[j])
			break ;
		str[i] = s[j];
		i++;
		j++;
	}
	str[i] = 0;
	while (s[j] == c && s[j])
		j++;
	return (j);
}

char	**split_token(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**strs;

	if (!s)
		return (0);
	strs = malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (strs == NULL)
		return (0);
	i = 0;
	j = 0;
	while (s[i] && (j < count_word(s, c) && count_word(s, c)))
	{
		strs[j] = malloc(count_char(s, c, i) + 1);
		if (!strs[j])
			return (0);
		i = ft_strccpy(s, strs[j], c, i);
		j++;
	}
	strs[j] = 0;
	return (strs);
}
