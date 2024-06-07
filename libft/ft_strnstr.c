/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 23:02:00 by bcai              #+#    #+#             */
/*   Updated: 2023/10/28 22:36:57 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*ph;
	size_t	i;

	ph = (char *)haystack;
	if (needle == 0 || *needle == '\0')
		return ((char *)haystack);
	i = 0;
	while (*ph && len > 0)
	{
		if (*ph == *needle)
		{
			while (ph[i] && ph[i] == needle[i] && len > 0)
			{
				i++;
				len--;
			}
			if (i == ft_strlen(needle) && len >= 0)
				return (ph);
		}
		ph++;
		if (len > 0)
			len--;
	}
	return (NULL);
}
/*
int	main(int argc, char *argv[])
{
	size_t	len;

	(void)argc;
	len = atoi(argv[3]);
	printf("my function %p\n", ft_strnstr(argv[1], argv[2], len));
	printf("official strnstr %p\n", strnstr(argv[1], argv[2], len));
	printf("haystack's address %p\n", argv[1]);
	return (0);
}*/
