/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:48:23 by uzyberaj          #+#    #+#             */
/*   Updated: 2024/12/04 14:00:02 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	c1;
	unsigned char	c2;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		c1 = (unsigned char)s1[i];
		c2 = (unsigned char)s2[i];
		if (c1 != c2 || c1 == '\0' || c2 == '\0')
			return (c1 - c2);
		i++;
	}
	return (0);
}

/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	if (argc > 3)
	{
		printf("tab1:%s\n", argv[1]);
		printf("tab2:%s\n", argv[2]);
		printf("ft_strncmp:%d\n", ft_strncmp(argv[1], argv[2], atoi(argv[3])));
		printf("strncmp:%d", strncmp(argv[1], argv[2], atoi(argv[3])));
	}
	else
		return (0);
}
*/