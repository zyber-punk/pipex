/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:51:48 by uzyberaj          #+#    #+#             */
/*   Updated: 2024/12/04 14:02:52 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dup;

	i = 0;
	while (src[i] != '\0')
		i++;
	dup = malloc(sizeof(char) * i + 1);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
/*
#include <stdio.h>
#include <string.h>

int	main(int argc, char *argv[])
{
	(void)argc;
	printf("Chaine source:%s\n", argv[1]);
	printf("ft_strdup:%s\n", ft_strdup(argv[1]));
	printf("strdup:%s\n", strdup(argv[1]));
	return (0);
}
*/