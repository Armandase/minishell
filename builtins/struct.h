#ifndef STRUCT_H
# define STRUCT_H

# include <stdbool.h>

typedef struct s_env_list
{
	char				*name;
	char				*value;
	bool				export_only;
	struct s_env_list	*next;
}						t_env_list;	

#endif
