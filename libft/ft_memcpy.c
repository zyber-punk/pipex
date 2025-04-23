/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:10:44 by uzyberaj          #+#    #+#             */
/*   Updated: 2024/12/04 14:03:45 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (!dest && !src && n > 0)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (n--)
		*d++ = *s++;
	return (dest);
}
/*
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	char	dest[50];
	char	dest1[50];
	char	dest2[50];

	if (argc > 2)
	{
		ft_memcpy(dest, argv[1], atoi(argv[2]));
		printf("%s\n", dest);
		memcpy(dest1, argv[1], atoi(argv[2]));
		printf("%s\n", dest1);
		memmove(dest2, argv[1], atoi(argv[2]));
		printf("%s\n", dest2);
	}
	else
		return (0);
}
*/