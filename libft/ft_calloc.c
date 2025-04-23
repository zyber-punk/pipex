/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:15:03 by uzyberaj          #+#    #+#             */
/*   Updated: 2024/12/04 14:10:56 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t number, size_t size)
{
	size_t	total;
	void	*ptr;

	if (size != 0 && number > SIZE_MAX / size)
		return (NULL);
	total = number * size;
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, total);
	return (ptr);
}

/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	size_t	size;
	int		*array;
	int		i;

	if (argc > 1)
	{
		size = sizeof(int);
		array = (int *)ft_calloc(atoi(argv[1]), size);
		i = 0;
		while (i < atoi(argv[1]))
		{
			printf("array[%d] = %d\n", i, array[i]);
			i++;
		}
	}
	else
		return (0);
}
*/