/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:19:47 by ulyssezyber       #+#    #+#             */
/*   Updated: 2024/12/04 14:04:51 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_size(int n)
{
	int	i;

	if (n == 0)
		i = 1;
	else
		i = 0;
	if (n < 0)
		n = -n;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int num)
{
	char		*dst;
	int			count;
	long		n;

	n = num;
	count = count_size(n);
	if (n < 0)
		count += 1;
	dst = malloc(sizeof(char) * (count + 1));
	if (!dst)
		return (0);
	dst[count] = '\0';
	if (n < 0)
	{
		dst[0] = '-';
		n = -n;
	}
	while (count > 0 && n != 0)
	{
		dst[--count] = (n % 10) + '0';
		n /= 10;
	}
	if (num == 0)
		dst[0] = '0';
	return (dst);
}

/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc > 1)
	{
		printf("%s\n", ft_itoa(atoi(argv[1])));
	}
	else
		return (0);
}
*/