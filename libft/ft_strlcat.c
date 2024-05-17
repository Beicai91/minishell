/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 22:36:23 by bcai              #+#    #+#             */
/*   Updated: 2023/11/30 17:15:33 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize < dst_len + 1)
		return (dstsize + src_len);
	else
	{
		i = dst_len;
		while (i < dstsize - 1 && *src)
			dst[i++] = *src++;
		dst[i] = '\0';
		return (dst_len + src_len);
	}
}
/*
Another way of thinking
size_t	ft_strlcat(char *dst, char 8src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize)
	{
		while (dst[i] != '\0' && i < dstsize)
			i++;
		if (dst[i] == '\0')
		{
			while (*src != '\0' && i < dstsize - 1)
				dst[i++] = *src++;
			dst[i] = '\0';
		}
	}
	while (*src++ != '\0')
		i++;
	return (i);
}
*/
/*
int	main(void)
{
	char	dst1[10] = "";
	char	src1[] = "lorem ipsum dolor sit amet";
	char	dst2[10] = "";
	char src2[] = "lorem ipsum dolor sit amet";
	size_t	res1 = ft_strlcat(dst1, src1, 0);
	size_t	res2 = strlcat(dst2, src2, 0);
	printf("my function %zu\n", res1);
	printf("official strlcat %zu\n", res2);
	printf("my function concatenate result %s\n", dst1);
	printf("official strlcat concatenate result %s\n", dst2);
	return (0);
}*/
