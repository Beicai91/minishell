/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:12:26 by bcai              #+#    #+#             */
/*   Updated: 2023/10/30 09:36:57 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list) * 1);
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
/*
int	main(void)
{
	t_list	*node1;
	t_list	*node2;

	char string[] = "moray";
	node1 = ft_lstnew(string);
	printf("%s\n", node1->content);

	int	num = 3;
	node2 = ft_lstnew(&num);
	printf("%d\n", *(int *)(node2->content));

	return (0);
}*/
