/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:13:47 by uzyberaj          #+#    #+#             */
/*   Updated: 2024/12/04 14:00:06 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;
	unsigned int	len_s;

	i = 0;
	len_s = ft_strlen(s);
	result = malloc(sizeof(char) * len_s + 1);
	if (!result)
		return (NULL);
	if (!s || !f)
		return (NULL);
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

/*
char	ft_toupper(unsigned int i, char c)
{
	(void) i;
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc > 1)
	{
		printf("%s\n", ft_strmapi(argv[1], ft_toupper));
	}
	else
		return (0);
}
*/