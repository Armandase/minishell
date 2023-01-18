#include "../builtins/builtins.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>

char	*ft_strjoin_space(char *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	i = -1;
	j = 0;
	if (s1)
	{
		while (s1[++i])
		{
			str[j] = s1[i];
			j++;
		}
	}
	free(s1);
	i = -1;
	while (s2[++i])
	{
		str[j] = s2[i];
		j++;
	}
	str[j] = ' ';
	str[j + 1] = '\0';
	return (str);
}

bool	search_file_name(char *file_name, char *wildcard)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (file_name[i])
	{
		while (wildcard[j] && file_name[i]
			&& wildcard[j] == file_name[i] && wildcard[j] != '*')
		{
			i++;
			j++;
		}
		if (wildcard[j] != file_name[i] && (wildcard[j] != '*' && j != 0))
			return (false);
		else
		{
			while (wildcard[j] && wildcard[j] == '*')
				j++;
			while (wildcard[j] && file_name[i] && wildcard[j] != file_name[i])
				i++;
			if (file_name[i] == '\0' && wildcard[j])
				return (false);
		}
	}
	return (true);
}

int	main(int ac, char **av)
{
	char			pwd[4096];
	struct dirent	*dir_ent;
	DIR				*dir;	
	char			**files;
	char			*joined_files;
	size_t			nb_files;
	int				i;

	if (ac != 3)
		return (1);
	joined_files = NULL;
	getcwd(pwd, 4096);
	dir = opendir(pwd);
	if (dir == NULL)
	{
		perror("Cannot open directory\n");
		return (1);
	}
	dir_ent = readdir(dir);
	joined_files = ft_strjoin_space(joined_files, av[1]);
	joined_files = ft_strjoin_space(joined_files, av[2]);
	while (dir_ent != NULL)
	{
		if (search_file_name(dir_ent->d_name, av[2]) == true)
			joined_files = ft_strjoin_space(joined_files, dir_ent->d_name);
		dir_ent = readdir(dir);
	}
	files = ft_split(joined_files, ' ');
	free(joined_files);
	i = 2;
	while (files[i])
	{
		printf("%s\n", files[i]);
		free(files[i]);
		i++;
	}
	free(files);
	closedir(dir);
	return (0);
}
