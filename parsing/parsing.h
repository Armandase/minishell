#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"

# define IN 1
# define OUT 2
# define APPEND 3
# define HEREDOC 4
# define PIPE 5

typedef struct s_cmd{
	char	**cmd;
	int		token;
	int		*quote;
	int		*exit;
}	t_cmd;

typedef struct s_token{
	char	*line;
	int		id;
}	t_token;

t_cmd	*parsing(char *line);
char	*strtok_unquote(char *str, const char *delim);
void	free_cmd(t_cmd *cmd);
char	**split_token(char const *s, char c, t_cmd *cmd);
t_token	*str_get_token(char *str, const char *delim);

#endif
