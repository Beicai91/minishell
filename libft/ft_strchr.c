/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <marvin@42lausanne.ch>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:28:01 by bcai              #+#    #+#             */
/*   Updated: 2023/11/30 16:21:46 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}
/*
Optimization
char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c && *s != '\0')
		s++;
	if (*s == (char)c)
		return (*s);
	return (NULL);
}
*/
/* This doesnt pass, I dont know why
char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	len;

	len = 0;
	while (s[len])
		len++;
	if (c == '\0')
		return ((char *)s + len);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}*/

// int	main(int argc, char *argv[])
// {
// 	(void)argc;
// 	char *p;
// 	char *p2;

// 	p = ft_strchr(argv[1], argv[2][0]);
// 	p2 = strchr(argv[1], argv[2][0]);
// 	printf("My strchr result is %p\n", p);
// 	printf("The official strchr result is %p", p2);
// 	return (0);
// }
