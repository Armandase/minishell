#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_env_list
{
	char	*name;
	char	*value;
	struct s_env_list	*next;
}						t_env_list;	

#endif
