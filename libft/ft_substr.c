/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:10:15 by ulyssezyber       #+#    #+#             */
/*   Updated: 2024/12/04 13:59:37 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	count;
	char	*cpy;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		cpy = malloc(1);
		if (!cpy)
			return (NULL);
		ft_memset(cpy, '\0', 1);
		return (cpy);
	}
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	cpy = malloc((len + 1) * sizeof(char));
	if (!cpy)
		return (NULL);
	i = start;
	count = 0;
	while (count < len && s[i])
		cpy[count++] = s[i++];
	ft_memset(cpy + count, '\0', 1);
	return (cpy);
}

/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc > 3)
	{
		printf("%s\n", ft_substr(argv[1], atoi(argv[2]), atoi(argv[3])));
	}
	else
		return (0);
}
*/