/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 22:54:19 by bcai              #+#    #+#             */
/*   Updated: 2023/11/29 17:16:41 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n)
	{
		if (*((unsigned char *)s) == (unsigned char)c)
			return ((unsigned char *)s);
		n--;
		s = (unsigned char *)s + 1;
	}
	return (NULL);
}
/*
int	main(int argc, char *argv[])
{
	(void)argc;
	char	*ptr;
	char	*ptr2;

	int	n = atoi(argv[3]);
	ptr = ft_memchr(argv[1], argv[2][0], n);
	printf("my function returns %p\n", ptr);
	ptr2 = ft_memchr(argv[1], argv[2][0], n);
	printf("my function returns %p\n", ptr2);
	return (0);
}*/
