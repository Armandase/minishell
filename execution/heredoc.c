#include "execution.h"

char	*cpy_without_nl(char *buffer)
{
	int		i;
	char	*ret;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		ret[i] = buffer[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

void	heredoc(t_exec *exec)
{
	char	*buf;
	char	*str;
	int		fd_buf[2];

	if (pipe(fd_buf) == -1)
		perror("Error");
	buf = get_next_line(0);
	str = cpy_without_nl(buf);
	while (ft_strcmp(exec->cmd[exec->i].cmd[0], buf) != 0)
	{
		ft_putstr_fd(buf, fd_buf[1]);
		free(buf);
		buf = get_next_line(0);
		free(str);
		str = cpy_without_nl(buf);
	}
	free(str);
	exec->fd_in = fd_buf[0];
	close(fd_buf[1]);
	free(buf);
}
