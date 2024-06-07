/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:32:47 by bcai              #+#    #+#             */
/*   Updated: 2023/10/30 12:05:02 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
/*
int	main(void)
{
	t_list	*node;
	t_list	*last;

	node = NULL;
	for (int i = 0; i < 3; i++)
	{
		t_list	*newnode;
		newnode = (t_list *)malloc(sizeof(t_list));
		if (!newnode)
			return (0);
		newnode->content = malloc(sizeof(int));
		*(int *)(newnode->content) = i;
		newnode->next = node;
		node = newnode;
	}
	last = ft_lstlast(node);
	printf("%d\n", *(int *)(last->content));
	while (node != NULL)
	{
		free(node);
		node = node->next;
	}
	return (0);
}*/
