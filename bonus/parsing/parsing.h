/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:00:30 by adamiens          #+#    #+#             */
/*   Updated: 2023/01/26 15:00:31 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../builtins/builtins.h"

# define IN 1
# define OUT 2
# define APPEND 3
# define HEREDOC 4
# define PIPE 5
# define FILES 6
# define CMD 7
# define BUILTINS 8
# define UN_FORK 9

typedef struct s_token{
	char	*line;
	int		id;
}	t_token;

t_cmd	*parsing(char *line, t_env_list *list_var);
char	*strtok_unquote(char *str, const char *delim);
void	free_cmd(t_cmd *cmd);
char	**split_token(t_token **token, t_env_list *list_var);
t_token	*str_get_token(char *str, const char *delim);
t_cmd	*list_new(void	*content, t_cmd *prev);

#endif
