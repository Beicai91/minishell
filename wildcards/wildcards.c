/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:53:00 by bcai              #+#    #+#             */
/*   Updated: 2024/05/17 10:53:06 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*check_wildcard(t_list *list)
{
	t_m		m;
	t_list	*ptr;

	m.check = check_list(&list);
	ptr = list;
	initialize_var_wild(&m);
	while (ptr != NULL)
	{
		if (ft_strchr((char *)ptr->content, '*'))
		{
			m.wild_count++;
			m.temp_list = open_cd((char *)ptr->content, m.temp_list, &m);
		}
		sort_array(&m.temp_list, &m);
		m.temp_w = merge_list(m.temp_w, m.temp_list);
		m.temp_list = NULL;
		ptr = ptr->next;
	}
	if (m.match_count == m.wild_count)
		list = remove_wildcards(list);
	list = merge_list(list, m.temp_w);
	if (m.check != NULL)
		list = add_check_node(list, m.check);
	return (list);
}

t_list	*remove_wildcards(t_list *list)
{
	t_list	*ptr;
	t_list	*prev;
	t_list	*temp;
	t_list	*to_free;

	ptr = list;
	prev = NULL;
	while (ptr != NULL)
	{
		if (prev)
		{
			if (ft_strchr((char *)ptr->content, '*'))
			{
				to_free = ptr;
				temp = ptr->next;
				ptr = prev;
				ptr->next = temp;
				free(to_free->content);
				free(to_free);
			}
		}
		prev = ptr;
		ptr = ptr->next;
	}
	return (list);
}

t_list	*merge_list(t_list *list, t_list *temp)
{
	t_list	*ptr;

	if (list == NULL && temp == NULL)
		return (NULL);
	if (list == NULL)
		return (temp);
	if (temp == NULL)
		return (list);
	ptr = list;
	while (ptr->next != NULL)
		ptr = ptr->next;
	if (temp)
		ptr->next = temp;
	return (list);
}

t_list	*open_cd(char *str, t_list *list, t_m *m)
{
	DIR				*dir;
	struct dirent	*entry;
	int				check;

	check = 0;
	dir = opendir(".");
	if (dir == NULL)
		return (NULL);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (pattern_match(entry->d_name, str))
		{
			if (check == 0)
			{
				check = 1;
				m->match_count++;
			}
			list = expand_list(list, entry->d_name);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (list);
}

t_list	*add_check_node(t_list *list, t_list *node)
{
	t_list	*ptr;

	ptr = list;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = node;
	ptr->next->next = NULL;
	return (list);
}
