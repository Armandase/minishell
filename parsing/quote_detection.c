#include "parsing.h"

void	find_next_quote(char c, char *str)
{
	int	i;
	
	i = 0;
	while (str[i] != '\0')
	{
		if (str == c)
			//find next quote and verif si cest la dernier
			//et si y en as pas chercher dans les autres tokens
			
	}
}

void	find_quote_in_token(char	**strs)
{
	int	i;
	int	j;
	int	simple;
	int	duo;

	i = 0;
	duo = 0;
	simple = 0;
	while (strs[i] != NULL)
	{
		j = 0;
		while (strs[i][j])
		{
			if (strs[i][j] == '\'' || strs[i][j] == '\"')
				find_next_quote('\'', strs[i])
		}
	}
}

