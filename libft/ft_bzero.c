/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:03:46 by uzyberaj          #+#    #+#             */
/*   Updated: 2024/12/04 14:05:20 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = '\0';
		i++;
	}
}

/*
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	if (argc > 2)
	{
		char	*str = argv[1];
		char	*str1 = argv[2];
		size_t	bytes;
		size_t	i;
		size_t	j;

		bytes = atoi(argv[3]);
		i = 0;
		ft_bzero(str, bytes);
		while (i < bytes && str[i] == '\0')
		{
			printf("\\0");
			i++;
			while (str[i] != '\0')
			{
				printf("%c", str[i]);
				i++;
			}
		}
		printf("\n");
		j = 0;
		bzero(str1, bytes);
		while (j < bytes && str1[j] == '\0')
		{
			printf("\\0");
			j++;
			while (str1[j] != '\0')
			{
				printf("%c", str1[j]);
				j++;
			}
		}
	}
	else
		return (0);
}
*/