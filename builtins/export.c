#include "builtins.h"

t_env_list	*main_export(char *name, char *value, t_env_list *list_var)
{
	t_env_list	*tmp;
	t_env_list	*new_var;

	tmp = list_var;
	new_var = ft_calloc(1, sizeof(t_env_list));
	if (new_var == NULL)
		return (NULL); //A faire plus propre avec un ft_exit_error
	new_var->name = name;
	new_var->value = value;
	new_var->next = NULL;
	if (list_var == NULL)
		return (new_var);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_var;
	return (list_var);
}
