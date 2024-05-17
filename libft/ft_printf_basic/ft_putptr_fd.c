/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthn_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:04:03 by bcai              #+#    #+#             */
/*   Updated: 2023/11/08 19:05:17 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	get_len(unsigned long long n)
{
	int	len;

	len = 0;
	while (n > 0)
	{
		len++;
		n = n / 16;
	}
	len += 2;
	return (len);
}

static void	create_string(char *s, unsigned long long n, int len)
{
	s[len] = '\0';
	while (len - 1 >= 2)
	{
		s[len - 1] = "0123456789abcdef"[n % 16];
		n = n / 16;
		len--;
	}
	s[0] = '0';
	s[1] = 'x';
}

int	ft_putptr_fd(unsigned long long n, int fd, int *error)
{
	int		len;
	char	*s;

	if (n == 0)
	{
		*error = write(1, "0x0", 3);
		return (3);
	}
	if (!n)
		*error = -1;
	len = get_len(n);
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
	{
		*error = -1;
		return (0);
	}
	create_string(s, n, len);
	*error = write(fd, s, ft_strlen(s));
	free(s);
	return (len);
}
/*
int	main(void)
{
	unsigned long	n;

	n = 2147483648;
	ft_puthnl_fd(n, 1);
	ft_puthnl_fd(&n, 1);
	printf("n's address is %p\n", &n);
	return (0);
}*/