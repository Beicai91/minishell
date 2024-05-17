/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <marvin@42lausanne.ch>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:37:23 by bcai              #+#    #+#             */
/*   Updated: 2023/10/26 12:18:20 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>
#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*original_dst;

	original_dst = dst;
	if (dst < src)
	{
		while (len--)
		{
			*(char *)dst = *(char *)src;
			dst++;
			src++;
		}
	}
	else
	{
		while (len--)
			*((char *)dst + len) = *((char *)src + len);
	}
	return (original_dst);
}
/*
int	main(void)
{
	char string[100] = "moraycatbanana";
	char *dst = string + 6;
	char *src = string + 3;
	printf("original dst1 is %s\n", ft_memmove(dst, src, 9));
	printf("%s\n", string);
	char string2[100] = "moraycatbanana";
	char *dst2 = string2 + 6;
	char *src2 = string2 + 3;
	printf("original dst2 is %s\n", ft_memmove(dst2, src2, 9));
	printf("%s\n", string2);
	return (0);
}*/
/*
int	main(void)
{
		char dst[] = "";
	printf("original dst is %p\n", dst);
		char src[] = "";
	printf("memmove return (%p\n", ft_memmove(dst, src, 1)));
		return (0);
}*/
