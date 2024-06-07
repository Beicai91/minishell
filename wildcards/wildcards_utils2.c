/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:52:42 by bcai              #+#    #+#             */
/*   Updated: 2024/05/17 12:37:13 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*check_list(t_list **list)
{
	t_list	*node;
	t_list	*ptr;

	ptr = *list;
	if (ptr != NULL)
	{
		while (ptr->next != NULL)
		{
			if (ft_strchr(ptr->next->content, '/'))
			{
				node = ptr->next;
				node->next = NULL;
				ptr->next = NULL;
				return (node);
			}
			ptr = ptr->next;
		}
	}
	return (NULL);
}

t_list	*expand_list(t_list *list, char *file_name)
{
	t_list	*ptr;
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	new_node->content = ft_strdup(file_name);
	new_node->next = NULL;
	ptr = list;
	if (list == NULL)
	{
		list = new_node;
		return (list);
	}
	while (ptr->next != NULL)
	{
		if (ft_strchr((char *)ptr->content, '*'))
		{
			ptr->content = ft_strdup(file_name);
			return (list);
		}
		ptr = ptr->next;
	}
	ptr->next = new_node;
	return (list);
}

int	pattern_match(char *file, char *pattern)
{
	while (*file)
	{
		if (*pattern == '*')
		{
			pattern++;
			if (!*pattern)
				return (1);
			while (*file && *file != *pattern)
				file++;
		}
		else if (*pattern == *file || *pattern == '?')
		{
			file++;
			pattern++;
		}
		else
			return (0);
	}
	while (*pattern == '*')
		pattern++;
	return (!*pattern);
}

void	free_t_list(t_list **list)
{
	t_list	*ptr;
	t_list	*temp;

	ptr = *list;
	while (ptr != NULL)
	{
		temp = ptr;
		ptr = ptr->next;
		free(temp->content);
		free(temp);
	}
}

void	initialize_var_wild(t_m *m)
{
	m->temp_list = NULL;
	m->temp_w = NULL;
	m->wild_count = 0;
	m->match_count = 0;
}
