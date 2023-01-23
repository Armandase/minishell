#include "parsing.h"
#include <stdlib.h>

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

static size_t	count_word(char *s, char c)
{
	size_t	i;
	size_t	count;
	int		tmp;

	i = 0;
	count = 1;
	tmp = 0;
	while (s[i] == c && s[i])
		i++;
	if (i == ft_strlen(s))
		return (0);
	while (s[i])
	{
		if (s[i] == '\'')
		{
			i++;
			tmp = find_next_quote(&s[i], '\'');
			i += tmp;
		}
		if (!s[i])
			break ;
		if (s[i] == '\"')
		{
			i++;
			tmp = find_next_quote(&s[i], '\"');
			i += tmp;
		}	
		if (!s[i])
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

void	get_dollar_value(char *s, size_t *count, size_t *i, t_env_list *list_var)
{
	int		k;
	char	*var;
	char	*str;

	k = 1;
	var = NULL;
	if (!s[k] || s[k] == ' ')
		return ;
	while (s[k] || s[k] == ' ')
		k++;
	var = malloc(sizeof(char) * k);
	k = 1;
	while (s[k] || s[k] == ' ')
	{
		var[k - 1] = s[k];
		k++;
	}
	var[k - 1] = '\0';
	str = search_send_var(var, &list_var);
	free(var);
	if (!str)
		*(i) += k - 1;
	else
		*count += ft_strlen(str);
	free(str);
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
		{
			i++;
			tmp = find_next_quote(&s[i], '\'');
			if (tmp == 0)
			{
				i += tmp + 1;
			}
			else
			{
				count += tmp;
				i += tmp;
			}
		}
		if (!s[i])
			break ;
		if (s[i] == '$')
			get_dollar_value((char *)&s[i], &count, &i, list_var);
		if (s[i] && s[i] == '\"')
		{
			i++;
			tmp = find_next_quote(&s[i], '\"');
			if (tmp == 0)
			{
				i += tmp + 1;
			}
			else
			{
				if (s[i] == '$')
					get_dollar_value((char *)&s[i], &count, &i, list_var);
				count += tmp;
				i += tmp;
			}
		}
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
	size_t	i;
	char	tmp;

	i = 0;
	while (str[i] != '$')
		i++;
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
	tmp_str = ft_strjoin_space(tmp_str, trunc_str);
	free(trunc_str);
	trunc_str = ft_strdup(&str[i]);
	str = ft_strjoin_space(tmp_str, trunc_str);
	if (trunc_str)
		free(trunc_str);
	return (str);
}

static size_t	ft_strccpy(char *s, char *str, size_t j, t_env_list *list_var)
{
	size_t	i;

	i = 0;
	while (s[j] == ' ' && s[j])
		j++;
	while (s[j])
	{
		if (s[j] == ' ')
			break ;
		if (s[j] == '$' && s[j + 1] && s[j + 1] != ' ')
			s = cpy_envp_val(s, list_var, &j);
		if (s[j] == '\'')
		{
			j++;
			if (!s[j])
				break ;
			while (s[j] && s[j] == '\'')
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
		if (s[j] == ' ' || !s[j])
			break ;
		if (s[j] == '$' && s[j + 1] && s[j + 1] != ' ')
		{
			s = cpy_envp_val(s, list_var, &j);
			j++;
		}
		if (s[j] == '\"')
		{
			j++;
			if (!s[j])
				break ;
			if (s[j] == '$' && s[j + 1] && s[j + 1] != ' ')
				s = cpy_envp_val(s, list_var, &j);
			while (s[j] && s[j] == '\"')
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
		if (s[j] == ' ' || !s[j])
			break ;
		str[i] = s[j];
		i++;
		j++;
	}
	str[i] = 0;
	while (s[j] == ' ' && s[j])
		j++;
	return (j);
}

char	**split_token(char *s, t_env_list *list_var)
{
	size_t	i;
	size_t	j;
	char	**strs;

	if (!s)
		return (0);
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
		i = ft_strccpy(s, strs[j], i, list_var);
		j++;
	}
	strs[j] = 0;
	return (strs);
}
