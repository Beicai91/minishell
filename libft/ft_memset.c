/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <marvin@42lausanne.ch>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:58:52 by bcai              #+#    #+#             */
/*   Updated: 2023/11/29 18:05:19 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	*ft_memset(void *s, int c, size_t len)
{
	size_t			i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)s)[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
Optimization
void	*ft_memset(void *s, int c, size_t len)
{
	while (len > 0)
		((unsigned char *)s)[--len] = (unsigned char)c;
	return (s);
}
*/
/*
int	main(int argc, char *argv[])
{
		(void)argc;

		size_t len = atoi(argv[3]);
		printf("my function %s\n", ft_memset(argv[1], argv[2][0], len));
		printf("the official memset %s", memset(argv[1], argv[2][0], len));
		return (0);
}*/
