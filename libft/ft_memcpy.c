/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:16:20 by bcai              #+#    #+#             */
/*   Updated: 2023/11/29 17:28:23 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*p;

	p = dst;
	while (n)
	{
		*(char *)dst = *(char *)src;
		dst++;
		src++;
		n--;
	}
	return (p);
}
/*
Optimization
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	if (dst == NULL || src == NULL)
		return (NULL);
	while (n-- > 0)
		((char *)dst)[n] = ((char *)src)[n];
}
*/
/*
int	main(void)
{
		char string[] = "moray banana";
		char *dst = string;
		printf("original dst1 %p\n", dst);
		char *src = string + 6;
		char string2[] = "moray banana";
		char *dst2 = string2;
		printf("original dst2 %p\n", dst2);
		char *src2 = string2 + 6;

		printf("my function return (%p\n", ft_memcpy(dst, src, 3)));
		printf("official memcpy return (%p\n", memcpy(dst2, src2, 3)));
		printf("my function %s\n", dst);
		printf("official memcpy %s\n", dst2);
		return (0);
}*/
