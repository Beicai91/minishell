/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:13:51 by bcai              #+#    #+#             */
/*   Updated: 2023/11/08 19:15:41 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putstr_len(char *s, int fd, int *error)
{
	int	len;

	if (s == NULL)
	{
		*error = write(fd, "(null)", 6);
		return (6);
	}
	len = ft_strlen(s);
	*error = write(fd, s, len);
	return (len);
}
