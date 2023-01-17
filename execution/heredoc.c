#include "execution.h"
#include <stdio.h>

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

int	heredoc(t_exec *exec)
{
	char	*buf;
	char	*str;
	int		fd_buf[2];
	int		len;

	if (pipe(fd_buf) == -1)
		perror("Error");
	ft_printf("> ");
	buf = get_next_line(0);
	str = cpy_without_nl(buf);
	len = ft_strlen(exec->cmd[exec->i].cmd[0]) + 1;
	while (ft_strncmp(exec->cmd[exec->i].cmd[0], str, len) != 0)
	{
		ft_printf("> ");
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
	return (fd_buf[0]);
}
