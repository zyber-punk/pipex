/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:37:57 by ulyssezyber       #+#    #+#             */
/*   Updated: 2024/12/04 14:02:46 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/*
void	ft_toupper(unsigned int i, char *c)
{
	(void) i;
	if (*c >= 'a' && *c <= 'z')
		*c -= 32;
}

#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc > 1)
	{
		ft_striteri(argv[1], ft_toupper);
		printf("%s\n", argv[1]);
	}
	else
		return (0);
}
*/