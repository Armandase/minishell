#include "parsing.h"

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
	if (var[0] == '?')
		str = ft_itoa(g_sh_state.exit_code);
	else
		str = search_send_var(var, &list_var);
	take_dollar_offset(str, i, count, k);
	*count += ft_strlen(var);
	free(var);
}

static size_t	count_char(char *s, char c, size_t i, t_env_list *list_var)
{
	size_t	count;

	count = 0;
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
		if (i > ft_strlen(s) || !s[i])
			break ;
		if (s[i] == c)
			break ;
		count++;
		i++;
	}
	return (count);
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
		if (simple_quote_check(s, str, j, &i))
			break ;
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
			if (s[*j] == '$' && s[*j + 1] && s[*j + 1] != ' '
				&& s[*j + 1] != '\"')
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
					if (s[*j] == '\"')
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
