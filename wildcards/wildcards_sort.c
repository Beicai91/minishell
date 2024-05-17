/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:52:02 by bcai              #+#    #+#             */
/*   Updated: 2024/05/17 10:52:19 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_array(t_list **array_files, t_m *m)
{
	t_list	*ptr;
	t_list	*smallest;
	t_list	*new;

	new = NULL;
	m->j = 0;
	ptr = *array_files;
	while (ptr != NULL)
	{
		m->j++;
		ptr = ptr->next;
	}
	ptr = *array_files;
	while (m->j > 0)
	{
		m->prev = NULL;
		smallest = find_smallest_and_remove(array_files, m);
		new = building_sorted(smallest, new);
		m->j--;
	}
	*array_files = new;
}

t_list	*building_sorted(t_list *smallest, t_list *new)
{
	t_list	*ptr;

	ptr = new;
	if (new == NULL)
	{
		new = smallest;
		smallest->next = NULL;
	}
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = smallest;
		smallest->next = NULL;
	}
	ptr = new;
	return (new);
}

t_list	*find_smallest_and_remove(t_list **array_files, t_m *m)
{
	find_smallest(array_files, m);
	while (m->ptr != NULL)
	{
		if (m->ptr->content == m->smlst->content)
		{
			if (m->prev == NULL)
			{
				if (m->ptr->next == NULL)
					return (m->smlst);
				*array_files = m->ptr->next;
				m->ptr = *array_files;
			}
			else
			{
				m->temp = m->ptr;
				m->ptr = m->prev;
				m->prev->next = m->temp->next;
			}
		}
		m->prev = m->ptr;
		m->ptr = m->ptr->next;
	}
	m->smlst->next = NULL;
	return (m->smlst);
}

void	find_smallest(t_list **array_files, t_m *m)
{
	m->ptr = *array_files;
	m->smlst = m->ptr;
	while (m->ptr != NULL)
	{
		if (ft_strcmp((char *)m->smlst->content, (char *)m->ptr->content) >= 0)
			m->smlst = m->ptr;
		m->ptr = m->ptr->next;
	}
	m->ptr = *array_files;
}
