/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 00:14:39 by bcai              #+#    #+#             */
/*   Updated: 2023/11/02 12:02:11 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	p = malloc(size * count);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, count * size);
	return (p);
}

/*
void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	size = count * size; // reuse size
	p = malloc(size);
	while (size > 0)
		p[--size] = 0; //assign 0 from tail to head
}
*/
