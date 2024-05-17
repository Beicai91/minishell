/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:06:49 by bcai              #+#    #+#             */
/*   Updated: 2023/11/01 10:42:57 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->next = NULL;
}
/*
int	main(void)
{
	t_list	*node;
	t_list	*new;
	t_list	*last;
	int		newcontent;

	newcontent = 3;
	new = ft_lstnew(&newcontent);
	node = NULL;
	for (int i = 0; i < 3; i++)
	{
		t_list	*newnode;
		newnode = ft_lstnew(&i);
		printf("newnode's content %d\n", *(int *)(newnode->content));
		ft_lstadd_front(&node, newnode);
	}
	printf("first node's content %d\n", *(int *)(node->content));
	ft_lstadd_back(&node, new);
	last = ft_lstlast(node);
	printf("%d\n", *(int *)(last->content));
	return (0);
}*/
