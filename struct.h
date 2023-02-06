/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:13:43 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/05 19:02:19 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int		*state;
	int		*signal;
	int		exit_code;
}			t_sh_state;

#endif
