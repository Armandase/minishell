#include "builtins.h"

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
