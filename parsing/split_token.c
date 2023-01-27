#include "parsing.h"

static int	find_next_quote(char *str, char c)
{
	int	i;

	i = 0;
	if (str[i] == c)
		return (i);
	while (str[i] != '\0')
	{
		i++;
		if (str[i] && str[i] == c)
			return (i - 1);
	}
	return (-1);
}

void	quote_offset(size_t *i, int *tmp, char *s, char c)
{
	(*i)++;
	*tmp = find_next_quote(&s[*i], c);
	*i += *tmp;
}

int	select_quote(char *s, size_t *i)
{
	int	tmp;

	tmp = 0;
	if (s[*i] == '\'')
		quote_offset(i, &tmp, s, '\'');
	if (!s[*i])
		return (1);
	if (s[*i] == '\"')
		quote_offset(i, &tmp, s, '\"');
	if (!s[*i])
		return (1);
	return (0);
}

static size_t	count_word(char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 1;
	while (s[i] == c && s[i])
		i++;
	if (i == ft_strlen(s))
		return (0);
	while (s[i])
	{
		if (select_quote(s, &i))
			break ;
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

void	take_dollar_offset(char *str, size_t *i, size_t *count, int k)
{
	if (!str)
		*(i) += k - 1;
	else
	{
		*count += ft_strlen(str);
		*i += k;
	}
	free(str);
}

void	get_dollar_value(char *s,
	size_t *count, size_t *i, t_env_list *list_var)
{
	int		k;
	char	*var;
	char	*str;

	k = 1;
	var = NULL;
	if (!s[k] || s[k] == ' ' || s[k] == '\'' || s[k] == '\"')
		return ;
	while (s[k] && s[k] != ' ' && s[k] != '\'' && s[k] != '\"')
		k++;
	var = malloc(sizeof(char) * k);
	k = 1;
	while (s[k] && s[k] != ' ' && s[k] != '\'' && s[k] != '\"')
	{
		var[k - 1] = s[k];
		k++;
	}
	var[k - 1] = '\0';
	str = search_send_var(var, &list_var);
	free(var);
	take_dollar_offset(str, i, count, k);
}

void	count_to_next_quote(char *s, size_t *i, size_t *count, t_env_list *list_var)
{
	int		tmp;
	char	c;

	c = s[*i];
	(*i)++;
	tmp = find_next_quote(&s[*i], c);
	if (tmp == 0)
	{
		*i += tmp + 1;
	}
	else
	{
		if (c == '\"' && s[*i] == '$')
			get_dollar_value((char *)&s[*i], count, i, list_var);
		*count += tmp;
		*i += tmp;
	}
}

static size_t	count_char(char *s, char c, size_t i, t_env_list *list_var)
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
			count_to_next_quote(s, &i, &count, list_var);
		if (!s[i])
			break ;
		if (s[i] == '$')
			get_dollar_value((char *)&s[i], &count, &i, list_var);
		if (s[i] && s[i] == '\"')
			count_to_next_quote(s, &i, &count, list_var);
		if (!s[i])
			break ;
		if (s[i] == c)
			break ;
		count++;
		i++;
	}
	return (count);
}

static char	*cpy_envp_val(char *str, t_env_list *list_var, size_t *j)
{
	char	*trunc_str;
	char	*tmp_str;
	char	*cpy_str;
	size_t	i;
	char	tmp;

	cpy_str = NULL;
	i = *j;
	tmp = str[i];
	str[i] = '\0';
	tmp_str = ft_strdup(str);
	str[i] = tmp;
	str += *j;
	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\"' && str[i] != '\'')
		i++;
	tmp = str[i];
	str[i] = '\0';
	trunc_str = search_send_var(str + 1, &list_var);
	str[i] = tmp;
	cpy_str = ft_strjoin(tmp_str, trunc_str);
	if (cpy_str)
	{
		str = ft_strjoin_space(cpy_str, &str[i]);
		free(tmp_str);
	}
	else
		str = ft_strjoin_space(tmp_str, &str[i]);
	free(trunc_str);
	return (str);
}

static char	*ft_strccpy(char *s, char *str, size_t *j, t_env_list *list_var)
{
	size_t	i;
	char	*cpy;

	i = 0;
	while (s[*j] && s[*j] == ' ')
		(*j)++;
	while (s[*j])
	{
		if (s[*j] == ' ')
			break ;
		if (s[*j] == '$' && s[*j + 1] && s[*j + 1] != ' ')
		{
			cpy = cpy_envp_val(s, list_var, j);
			free(s);
			s = cpy;
		}
		if (s[*j] == '\'')
		{
			(*j)++;
			if (!s[*j])
				break ;
			while (s[*j] && s[*j] == '\'')
				(*j)++;
			while (s[*j])
			{
				str[i] = s[*j];
				(*j)++;
				i++;
				if (s[*j] == '\'')
				{
					(*j)++;
					break ;
				}
			}
		}
		if (s[*j] == ' ' || !s[*j])
			break ;
		if (s[*j] == '$' && s[*j + 1] && s[*j + 1] != ' ')
		{
			cpy = cpy_envp_val(s, list_var, j);
			free(s);
			s = cpy;
		}
		if (s[*j] == '\"')
		{
			(*j)++;
			if (!s[*j])
				break ;
			if (s[*j] == '$' && s[*j + 1] && s[*j + 1] != ' ' && s[*j + 1] != '\"')
			{
				cpy = cpy_envp_val(s, list_var, j);
				free(s);
				s = cpy;
			}
			while (s[*j] && s[*j] == '\"')
				(*j)++;
			while (s[*j])
			{
				str[i] = s[*j];
				i++;
				(*j)++;
				if (s[*j] == '\"')
				{
					(*j)++;
					break ;
				}
				if (s[*j] == '$' && s[*j + 1] && s[*j + 1] != ' ')
				{
					cpy = cpy_envp_val(s, list_var, j);
					free(s);
					s = cpy;
				}
			}
		}
		if (!s[*j] || s[*j] == ' ')
			break ;
		str[i] = s[*j];
		i++;
		(*j)++;
	}
	str[i] = 0;
	while (s[*j] && s[*j] == ' ')
		(*j)++;
	return (s);
}

char	**split_token(t_token **token, t_env_list *list_var)
{
	size_t	i;
	size_t	j;
	char	**strs;
	char	*s;

	if (!token || !(*token) || !(*token)->line)
		return (0);
	s = ft_strdup((*token)->line);
	strs = malloc(sizeof(char *) * (count_word(s, ' ') + 1));
	if (strs == NULL)
		return (0);
	i = 0;
	j = 0;
	while (s[i] && (j < count_word(s, ' ') && count_word(s, ' ')))
	{
		strs[j] = malloc(count_char(s, ' ', i, list_var) + 1);
		if (!strs[j])
			return (0);
		s = ft_strccpy(s, strs[j], &i, list_var);
		j++;
	}
	strs[j] = 0;
	free((*token)->line);
	(*token)->line = s;
	return (strs);
}
