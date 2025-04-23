/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:57:20 by uzyberaj          #+#    #+#             */
/*   Updated: 2024/12/04 13:59:30 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c -= 32;
	return (c);
}

/*
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char *argv[])
{
	if (argc > 1)
	{
		printf("%c\n", ft_toupper(atoi(argv[1])));
		printf("%c\n", toupper(atoi(argv[1])));
	}
	else
		return (0);
}
*/