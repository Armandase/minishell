#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct cmd_s{
	char	**cmd;
}cmd_t;

void	parsing(char *line, char **envp);
char	*strtok_unquote(char *str, const char *delim);
void	free_cmd(cmd_t *cmd);
char	**split_token(char const *s, char c);

#endif
