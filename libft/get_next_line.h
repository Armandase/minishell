/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:25:54 by adamiens          #+#    #+#             */
/*   Updated: 2022/12/12 09:32:34 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
char	*ft_get_strjoin(char *s1, char *s2);
char	*ft_get_strndup(char *s, int len);
void	ft_get_substr(char *s);
size_t	ft_get_strlen(char *str);
void	*ft_get_calloc(size_t nmemb, size_t size);
void	ft_nlcpy(char *buffer, char *str, int i);

#endif
