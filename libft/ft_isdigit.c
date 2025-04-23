/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:04:45 by uzyberaj          #+#    #+#             */
/*   Updated: 2024/12/04 14:04:59 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if ((c >= 48 && c <= 57))
		return (1);
	else
		return (0);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int	main(int argc, char *argv[])
{
	if (argc > 1)
	{
		printf("%d\n", ft_isdigit(atoi(argv[1])));
		printf("%d\n", isdigit(atoi(argv[1])));
		return (0);
	}
	else
		return (0);
}
*/