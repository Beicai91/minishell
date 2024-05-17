/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:37:23 by bcai              #+#    #+#             */
/*   Updated: 2023/10/30 12:06:18 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_lstsize(t_list *lst)
{
	int		len;

	len = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}
/*
int	main(void)
{
	int	i;
	t_list	*node;
	int		len;

	node = NULL;
	for (i = 0; i < 3; i++)
	{
		t_list	*newnode;
		newnode = malloc(sizeof(t_list));
		if(!newnode)
			return (0);
		newnode->content = malloc(sizeof(int));
		*(int *)(newnode->content) = i;
		newnode->next = node;
		node = newnode;
	}
	len = ft_lstsize(node);
	while (node != NULL)
	{
		free(node);
		node = node->next;
	}
	printf("%d\n", len);
	return (0);
}*/
