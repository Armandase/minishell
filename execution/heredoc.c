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
	if (buf == NULL)
		ft_printf("\n");
	str = cpy_without_nl(buf);
	g_sh_state.state = HERE_DOC;
	len = ft_strlen(cmd->cmd[0]) + 1;
	while (ft_strncmp(cmd->cmd[0], str, len) != 0)
	{
		ft_printf("> ");
		ft_putstr_fd(buf, fd_buf[1]);
		buf = get_next_line(0);
		if (buf == NULL)
			ft_printf("\n");
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
		return (-2);
	}
	return (fd_buf[0]);
}
