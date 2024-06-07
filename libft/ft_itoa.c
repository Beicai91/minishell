/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 18:40:50 by bcai              #+#    #+#             */
/*   Updated: 2023/11/09 13:59:45 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

int	get_len(int n)
{
	int				len;
	unsigned int	un;

	len = 1;
	if (n < 0)
	{
		un = -n;
		len++;
	}
	else
		un = n;
	while (un / 10 > 0)
	{
		un = un / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*p;
	unsigned int	un;
	int				len;

	len = get_len(n);
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	if (n < 0)
		un = -n;
	else
		un = n;
	p[len] = '\0';
	while (len - 1 >= 0)
	{
		p[len - 1] = un % 10 + 48;
		un = un / 10;
		len--;
	}
	if (n < 0)
		p[0] = '-';
	return (p);
}
/*
int	main(int argc, char *argv[])
{
	(void)argc;
	char *p;

	int	n = atoi(argv[1]);
	p = ft_itoa(n);
	printf("%s\n", p);
	free(p);
	return (0);
}*/
