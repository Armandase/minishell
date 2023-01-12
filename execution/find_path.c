#include "execution.h"

char	*ft_find_path(char **envp)
{
	int		i;
	char	*ret;
	size_t	len;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 4) == 0)
		{
			len = ft_strlen(envp[i]) + 1;
			ret = malloc(sizeof(char) * len);
			if (!ret)
				return (NULL);
			ft_strlcpy(ret, envp[i], len);
			return (ret);
		}
		i++;
	}
	return (NULL);
}

char	**get_path(char **envp)
{
	int		len;
	char	*tmp;
	char	*path;
	char	**directory;

	path = ft_find_path(envp);
	if (!path)
		exit(1);
	directory = ft_split(path, ':');
	free(path);
	if (!directory)
		exit(1);
	len = ft_strlen(directory[0]);
	tmp = ft_substr(directory[0], 5, len);
	if (!tmp)
		return (NULL);
	free(directory[0]);
	directory[0] = tmp;
	return (directory);
}

void	cpy_path(char **cmd, char **directory)
{
	int		j;
	char	*tmp;
	char	*str;

	j = 0;
	while (directory[j])
	{
		tmp = ft_strjoin(directory[j], "/");
		str = ft_strjoin(tmp, *cmd);
		free(tmp);
		if (access(str, X_OK) == 0)
		{
			free(*cmd);
			*cmd = ft_strdup(str);
			free(str);
			return ;
		}
		else
			free(str);
		j++;
	}
	*cmd = NULL;
}

void	get_cmd_path(char **cmd, char **envp)
{
	char	**directories;

	directories = get_path(envp);
	cpy_path(cmd, directories);
}