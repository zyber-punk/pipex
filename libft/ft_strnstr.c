/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:39:38 by uzyberaj          #+#    #+#             */
/*   Updated: 2024/12/04 13:59:57 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] != '\0' && i < len)
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (little[j] && big[i + j] == little[j] && (i + j) < len)
				j++;
			if (little[j] == '\0')
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <bsd/string.h>

int	main(int argc, char *argv[])
{
	if (argc > 3)
	{
		printf("%s\n", ft_strnstr(argv[1], argv[2], atoi(argv[3])));
		printf("%s\n", strnstr(argv[1], argv[2], atoi(argv[3])));
	}
	else
		return (0);
}
*/