/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:53:13 by uzyberaj          #+#    #+#             */
/*   Updated: 2024/12/04 14:04:01 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;
	unsigned char		ch;

	ptr = (const unsigned char *)s;
	ch = (unsigned char)c;
	while (n--)
	{
		if (*ptr == ch)
			return ((void *)ptr);
		ptr++;
	}
	return (NULL);
}

/*
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	if (argc > 2)
	{
		printf("%s\n", ft_memchr(argv[1], atoi(argv[2]), atoi(argv[3])));
		printf("%s\n", memchr(argv[1], atoi(argv[2]), atoi(argv[3])));
	}
	else
		return (0);
}
*/