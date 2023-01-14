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
