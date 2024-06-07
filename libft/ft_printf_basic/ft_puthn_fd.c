/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthn_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:05:46 by bcai              #+#    #+#             */
/*   Updated: 2023/11/10 11:05:50 by bcai             ###   ########.fr       */
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
		n = n / 16;
	}
	return (len);
}

static void	create_string(char *s, int len, unsigned int n, char c)
{
	s[len] = '\0';
	while (n > 0)
	{
		if (c == 'x')
			s[len - 1] = "0123456789abcdef"[n % 16];
		else if (c == 'X')
			s[len - 1] = "0123456789ABCDEF"[n % 16];
		n = n / 16;
		len--;
	}
}

int	ft_puthn_fd(unsigned int n, int fd, char c, int *error)
{
	int		len;
	char	*s;

	if (n == 0)
		return (ft_putchar_len('0', 1, error));
	if (n < 0)
		*error = -1;
	len = get_len(n);
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
	{
		*error = -1;
		return (0);
	}
	create_string(s, len, n, c);
	*error = write(fd, s, ft_strlen(s));
	free(s);
	return (len);
}
/*
int	main(void)
{
	unsigned long	n;

	n = 1000;
	ft_puthn_fd(n, 1, 'x');
	//printf("%x", n);
	return (0);
}*/