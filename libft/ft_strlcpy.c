/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:35:00 by uzyberaj          #+#    #+#             */
/*   Updated: 2024/12/04 14:02:34 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i] && size > i + 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < size)
		dest[i] = '\0';
	while (src[i])
		i++;
	return (i);
}

/*
#include <stdio.h>
#include <bsd/string.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	char	dest[50];

	if (argc > 2)
	{
		printf("%zu\n", ft_strlcpy(dest, argv[1], atoi(argv[2])));
		printf("%s\n", dest);
		printf("%zu\n", strlcpy(dest, argv[1], atoi(argv[2])));
		printf("%s", dest);
	}
	else
		return (0);
}
*/