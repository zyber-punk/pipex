/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:58:42 by uzyberaj          #+#    #+#             */
/*   Updated: 2024/12/04 14:03:17 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

/*
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	int	i;

	if (argc > 2)
	{
		i = 0;
		while (argv[1][i])
		{
			ft_putchar_fd(argv[1][i], atoi(argv[2]));
			i++;
		}
	}
	else
		return (0);
}
*/