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

typedef struct s_cmd
{
	char			**cmd;
	int				token;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_exec
{
	t_cmd		*cmd;
	int			*tab_pid;
	int			nb_fork;
	int			fd_out;
	int			fd_in;
	t_env_list	**list_var;
	char		**envp;
}				t_exec;

typedef struct s_sh_state
{
	int		state;
	bool	check_signal;
}			t_sh_state;

#endif
