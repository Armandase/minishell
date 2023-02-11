/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:12:59 by ulayus            #+#    #+#             */
/*   Updated: 2023/02/11 15:07:22 by ulayus           ###   ########.fr       */
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
		if (buf == NULL && g_sh_state.check_signal == false)
		{
			ft_putstr_fd("warning: here-document stopped by end-of-file\n", 2);
			break ;
		}
		else if (buf == NULL && g_sh_state.check_signal == true)
			break ;
		free(str);
		str = cpy_without_nl(buf);
	}
	free(str);
	close(fd_buf[1]);
	free(buf);
}

static void	print_error_null(int fd, int fd_buf[2])
{
	ft_putstr_fd("warning: here-document stopped by end-of-file\n", 2);
	ft_putstr_fd("\n", fd_buf[1]);
	close(fd);
	close(fd_buf[1]);
}

static int	restore_stdin(int fd, int fd_buf[2])
{
	dup2(fd, 0);
	close(fd_buf[1]);
	close(fd_buf[0]);
	close(fd);
	ft_printf("\n");
	return (-2);
}

int	heredoc(t_cmd *cmd)
{
	char	*buf;
	char	*str;
	int		fd_buf[2];
	int		fd;

	if (pipe(fd_buf) == -1)
		perror("Error");
	fd = dup(0);
	ft_printf("> ");
	buf = get_next_line(0);
	if (buf == NULL && g_sh_state.check_signal == false)
	{
		print_error_null(fd, fd_buf);
		return (fd_buf[0]);
	}
	if (buf != NULL)
	{
		str = cpy_without_nl(buf);
		get_line(cmd, str, buf, fd_buf);
	}
	if (g_sh_state.check_signal == true)
		return (restore_stdin(fd, fd_buf));
	close(fd);
	return (fd_buf[0]);
}
