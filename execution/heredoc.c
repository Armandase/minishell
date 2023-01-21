#include "execution.h"

extern t_sh_state	g_sh_state;

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

int	heredoc(t_cmd *cmd)
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
	free(buf);
	g_sh_state.state = HERE_DOC;
	len = ft_strlen(exec->cmd[exec->i].cmd[0]) + 1;
	while (ft_strncmp(exec->cmd[exec->i].cmd[0], str, len) != 0)
	{
		ft_printf("> ");
		ft_putstr_fd(buf, fd_buf[1]);
		buf = get_next_line(0);
		free(str);
		str = cpy_without_nl(buf);
		if (g_sh_state.check_signal == true)
			break ;
	}
	free(str);
	close(fd_buf[1]);
	free(buf);
	if (g_sh_state.check_signal == true)
	{
		close(fd_buf[0]);
		exit(130);
	}
	return (fd_buf[0]);
}
