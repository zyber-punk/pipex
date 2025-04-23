/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:56:41 by uzyberaj          #+#    #+#             */
/*   Updated: 2024/12/04 14:03:22 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = c;
		i++;
	}
	return (s);
}
/*
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	if (argc > 4)
	{
		char	*str = argv[1];
		char	*str1 = argv[2];
		int	c;
		size_t	bytes;
		size_t	i;
		size_t	j;

		bytes = atoi(argv[4]);
		c = atoi(argv[3]);
		i = 0;
		ft_memset(str, c, bytes);
		while (i < bytes && str[i])
		{
			printf("%c", str[i]);
			i++;
		}
		printf("\n");
		j = 0;
		memset(str1, c, bytes);
		while (j < bytes && str1[j])
		{
			printf("%c", str1[j]);
			j++;
		}
	}
	else
		return (0);
}
*/