/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:53:19 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/06 10:34:13 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	get_line(t_cmd *cmd, char *str, char *buf, int fd_buf[2])
{
	int	len;

	len = ft_strlen(cmd->cmd[0]) + 1;
	while (ft_strncmp(cmd->cmd[0], str, len) != 0)
	{
		ft_printf("> ");
		ft_putstr_fd(buf, fd_buf[1]);
		free(buf);
		buf = NULL;
		buf = get_next_line(0);
		if (buf == NULL)
		{
			ft_putstr_fd("warning: here-document stopped by end-of-file\n", 2);
			break ;
		}
		free(str);
		str = cpy_without_nl(buf);
		if (g_sh_state.check_signal == true)
			break ;
	}
	free(str);
	close(fd_buf[1]);
	free(buf);
}

int	heredoc(t_cmd *cmd)
{
	char	*buf;
	char	*str;
	int		fd_buf[2];

	if (pipe(fd_buf) == -1)
		perror("Error");
	ft_printf("> ");
	buf = get_next_line(0);
	if (buf == NULL)
	{
		ft_putstr_fd("warning: here-document stopped by end-of-file", 2);
		ft_putstr_fd("\n", fd_buf[1]);
		close (fd_buf[1]);
		return (fd_buf[0]);
	}
	str = cpy_without_nl(buf);
	get_line(cmd, str, buf, fd_buf);
	if (g_sh_state.check_signal == true)
	{
		close(fd_buf[0]);
		return (-2);
	}
	return (fd_buf[0]);
}
