/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:09:35 by uzyberaj          #+#    #+#             */
/*   Updated: 2024/12/04 14:03:01 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_tokens(char const *s, char delimeter)
{
	size_t	tokens;
	bool	inside_token;

	tokens = 0;
	while (*s)
	{
		inside_token = 0;
		while (*s == delimeter && *s)
			s++;
		while (*s != delimeter && *s)
		{
			if (!inside_token)
			{
				tokens++;
				inside_token = 1;
			}
			s++;
		}
	}
	return (tokens);
}

int	safe_malloc(char **token_v, int position, size_t buffer)
{
	int	i;

	i = 0;
	token_v[position] = malloc(buffer);
	if (!token_v[position])
	{
		while (i < position)
			free(token_v[i++]);
		free(token_v);
		return (1);
	}
	return (0);
}

int	fill(char **token_v, char const *s, char delimeter)
{
	size_t	len;
	int		i;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s == delimeter && *s)
			s++;
		while (*s != delimeter && *s)
		{
			len++;
			s++;
		}
		if (len > 0)
		{
			if (safe_malloc(token_v, i, len + 1))
				return (1);
			ft_strlcpy(token_v[i], s - len, len + 1);
			i++;
		}
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	tokens;
	char	**token_v;

	if (!s)
		return (NULL);
	tokens = 0;
	tokens = count_tokens(s, c);
	token_v = malloc(sizeof(char *) * (tokens + 1));
	if (!token_v)
		return (NULL);
	token_v[tokens] = NULL;
	if (fill(token_v, s, c))
		return (NULL);
	return (token_v);
}

/* 
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc > 2)
	{
		char	**v;

		v = ft_split(argv[1], *argv[2]);
		while (*v)
			printf("%s\n", *v++);
	}
	else
		return (0);
}
 */