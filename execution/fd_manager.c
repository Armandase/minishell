/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:02:56 by adamiens          #+#    #+#             */
/*   Updated: 2023/01/25 17:04:17 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	open_pipe(int tab_pipe[2][2], int i)
{
	close(tab_pipe[i % 2][1]);
	close(tab_pipe[i % 2][0]);
	pipe(tab_pipe[i % 2]);
}

void	close_pipe(int tab_pipe[2][2])
{
	close(tab_pipe[1][1]);
	close(tab_pipe[1][0]);
	close(tab_pipe[0][1]);
	close(tab_pipe[0][0]);
}
