/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 23:15:01 by ulayus            #+#    #+#             */
/*   Updated: 2023/01/27 15:18:49 by ulayus           ###   ########.fr       */

#include "libft.h"

static unsigned long long	ft_abs(long long n)
{
	if (n > 0)
		return ((unsigned long long)n);
	return ((unsigned long long)n * -1);
}

static int	nb_digits(long long n)
{
	int	count;

	count = 1;
	while (n >= 10 || n <= -10)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_lltoa(long long n)
{
	int		i;
	char	*str;

	if (!n)
		return (ft_strdup("0"));
	if (n > 0)
		i = nb_digits(n);
	else
		i = nb_digits(n) + 1;
	str = malloc(i + 1);
	if (!str)
		return (0);
	if (n < 0)
		str[0] = '-';
	str[i--] = 0;
	while ((i >= 0 && n > 0) || (i >= 1 && n < 0))
	{
		str[i--] = ft_abs(n) % 10 + 48;
		n = n / 10;
	}
	return (str);
}
