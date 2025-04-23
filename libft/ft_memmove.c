/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:19:46 by uzyberaj          #+#    #+#             */
/*   Updated: 2024/12/04 14:03:26 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;

	if (!dest && !src)
		return (NULL);
	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	if (d > s && d < s + n)
	{
		while (n--)
			d[n] = s[n];
	}
	else
	{
		while (n--)
			*d++ = *s++;
	}
	return (dest);
}

/*
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	if (argc > 2)
	{
		char	dest[50];
		char	dest1[50];

		ft_memmove(dest, argv[1], atoi(argv[2]));
		printf("%s\n", dest);
		memmove(dest1, argv[1], atoi(argv[2]));
		printf("%s\n", dest1);
	}
}
*/