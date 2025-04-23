/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 13:15:14 by uzyberaj          #+#    #+#             */
/*   Updated: 2024/12/04 14:02:30 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*
#include <stdio.h>
#include <string.h>

int	main(int argc, char *argv[])
{
	if (argc > 1)
	{
		printf("%lu\n", ft_strlen(argv[1]));
		printf("%lu\n", strlen(argv[1]));
		return (0);
	}
	else
		return (0);
}
*/