#include "builtins.h"

char	*ft_strjoin_space(char *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	i = -1;
	j = 0;
	if (s1)
	{
		while (s1[++i])
		{
			str[j] = s1[i];
			j++;
		}
	}
	free(s1);
	i = -1;
	while (s2[++i])
	{
		str[j] = s2[i];
		j++;
	}
	str[j] = ' ';
	str[j + 1] = '\0';
	return (str);
}

size_t	env_list_size(t_env_list *list_var)
{
	t_env_list	*tmp;
	size_t		len;

	tmp = list_var;
	len = 0;
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}

char	**env_export(t_env_list *list_var)
{
	t_env_list	*tmp;
	size_t		len;
	char		**env_var;
	char		*line;
	int			i;

	len = env_list_size(list_var);
	env_var = ft_calloc(sizeof(char *), len + 1);
	if (env_var == NULL)
		return (NULL);
	i = 0;
	tmp = list_var;
	while (tmp != NULL)
	{
		line = ft_strjoin(tmp->name, "=");
		env_var[i] = ft_strjoin(line, tmp->value);
		free(line);
		tmp = tmp->next;
		i++;
	}
	return (env_var);
}

bool	search_var(char *var, t_env_list **list_var)
{
	t_env_list	*tmp;
	int			i;

	tmp = *list_var;
	i = 0;
	while (tmp)
	{
		if (ft_strcmp(var, tmp->name) == false)
			return (true);
		tmp = tmp->next;
		i++;
	}
	return (false);
}

char	*search_send_var(char *var, t_env_list **list_var)
{
	t_env_list	*tmp;
	int			i;

	tmp = *list_var;
	i = 0;
	while (tmp)
	{
		if (ft_strcmp(var, tmp->name) == false)
		{
			var = ft_strdup(tmp->value);
			return (var);
		}
		tmp = tmp->next;
		i++;
	}
	return (NULL);
}

void	search_replace_var(char *name, char *value, t_env_list **list_var)
{
	t_env_list	*tmp;

	tmp = *list_var;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == false)
		{
			free(tmp->value);
			tmp->value = value;
			tmp->export_only = false;
		}
		tmp = tmp->next;
	}
}
