/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:58:52 by bcai              #+#    #+#             */
/*   Updated: 2023/11/09 14:04:27 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putd(int n, int *error)
{
	int		print_len;
	char	*str;

	str = ft_itoa(n);
	if (!str)
	{
		*error = -1;
		return (0);
	}
	print_len = ft_strlen(str);
	*error = write(1, str, print_len);
	free(str);
	return (print_len);
}
