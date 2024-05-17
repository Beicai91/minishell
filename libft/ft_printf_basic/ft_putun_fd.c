/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putun_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:37:01 by bcai              #+#    #+#             */
/*   Updated: 2023/11/08 19:05:29 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	get_len(unsigned int n)
{
	int	len;

	len = 0;
	while (n > 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

int	ft_putun_fd(unsigned int n, int fd, int *error)
{
	int		len;
	int		len_cpy;
	char	*str;

	if (n < 0)
		*error = -1;
	len = get_len(n);
	len_cpy = len;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
	{
		*error = -1;
		return (0);
	}
	while (len - 1 >= 0)
	{
		str[len - 1] = n % 10 + 48;
		n = n / 10;
		len--;
	}
	str[len_cpy] = '\0';
	*error = write(fd, str, len_cpy);
	free(str);
	return (len_cpy);
}
/*
int	main(void)
{
	unsigned int n;
	int	len;

	n = 4294967295;
	len = ft_putun_fd(n, 1);
	printf("%d", len);
	return (0);
}*/