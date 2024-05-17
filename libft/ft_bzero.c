/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <marvin@42lausanne.ch>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:58:52 by bcai              #+#    #+#             */
/*   Updated: 2023/11/02 12:04:01 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	size_t			i;

	if (!s)
		return ;
	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}
/*
Optimization
void	ft_bzero(void *s, size_t n)
{
	while (n > 0)
		((unsigned char *)s)[--n] = 0;  //write from the tail to head 0
}
*/

/*
int	main(int argc, char *argv[])
{
		(void)argc;
		size_t n;

		n = atoi(argv[2]);
		ft_bzero(argv[1], n);
		bzero(argv[1], n);
		printf("my function %s\n", argv[1]);
		printf("official bzero %s\n", argv[1]);
		return (0);
}*/
