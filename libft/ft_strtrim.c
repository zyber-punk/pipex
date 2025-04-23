/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:57:15 by ulyssezyber       #+#    #+#             */
/*   Updated: 2024/12/04 13:59:45 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;

	if (!s1 || !set)
		return (0);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[start]) && start <= end)
		start++;
	if (start > end)
		return (ft_strdup(s1 + end + 1));
	while (ft_strchr(set, s1[end]) && end >= 0)
		end--;
	str = malloc(end - start + 2);
	if (!str)
		return (0);
	ft_strlcpy(str, &s1[start], end - start + 2);
	return (str);
}

/*
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        printf("%s\n", ft_strtrim(argv[1], argv[2]));
    }
    else
        return (0);
}
*/