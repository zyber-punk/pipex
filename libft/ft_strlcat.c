/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:37:00 by uzyberaj          #+#    #+#             */
/*   Updated: 2024/12/04 14:02:38 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	size_src;
	size_t	size_dest;

	i = 0;
	j = 0;
	size_src = ft_strlen(src);
	size_dest = ft_strlen(dest);
	if (size <= size_dest)
		return (size + size_src);
	i = size_dest;
	while (i < size - 1 && src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (size_dest + size_src);
}
/*
#include <stdio.h>
#include <bsd/string.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	if (argc > 5)
	{
		printf("ft_strlcat:%zu\n", ft_strlcat(argv[1], argv[2], atoi(argv[5])));
		printf("strlcat:%zu\n", strlcat(argv[3], argv[4], atoi(argv[5])));
	}
	else
		return (0);
}
*/