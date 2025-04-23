/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:35:04 by uzyberaj          #+#    #+#             */
/*   Updated: 2024/12/04 13:59:53 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last_occurrence = NULL;

	while (*s)
	{
		if (*s == (char)c)
			last_occurrence = s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return ((char *)last_occurrence);
}

/*
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	if (argc > 2)
	{
		printf("%s\n", ft_strrchr(argv[1], atoi(argv[2])));
		printf("%s\n", strrchr(argv[1], atoi(argv[2])));
	}
	else
		return (0);
}
*/