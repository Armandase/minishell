/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:01:26 by adamiens          #+#    #+#             */
/*   Updated: 2023/01/25 18:59:34 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lenint(long long n)
{
	int			i;
	long long	number;

	i = 1;
	number = n;
	if (n < 0)
	{
		i++;
		number *= -1;
	}
	if (number < 10)
		return (i);
	while (number >= 10)
	{
		number /= 10;
		i++;
	}
	return (i);
}

static char	*ft_negative(long long n, char *ret, int nlen)
{
	int		counter;
	long	i;

	counter = 0;
	if (n == 0)
	{
		ret[0] = '0';
		return (ret);
	}
	i = (long)n;
	i *= -1;
	ret[0] = '-';
	while (i > 0)
	{
		ret[(nlen - 1) - counter] = i % 10 + '0';
		i /= 10;
		counter++;
	}
	return (ret);
}

char	*ft_lltoa(long long n)
{
	size_t		i;
	int			counter;
	char		*ret;
	long long	nlen;

	nlen = ft_lenint(n);
	ret = malloc(nlen + 1);
	if (!ret)
		return (NULL);
	counter = 0;
	i = n;
	if (n <= 0)
	{
		ret = ft_negative(n, ret, nlen);
		ret[nlen] = '\0';
		return (ret);
	}
	while (i > 0)
	{
		ret[(nlen - 1) - counter] = i % 10 + '0';
		counter++;
		i /= 10;
	}
	ret[nlen] = '\0';
	return (ret);
}
