/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_in_out.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:51:38 by bcai              #+#    #+#             */
/*   Updated: 2024/05/17 10:51:54 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*open_cd_in_out(char *str, t_m *m)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*array_files;
	t_list			*array_list;

	array_files = NULL;
	dir = opendir(".");
	if (dir == NULL)
		return (NULL);
	array_list = NULL;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (pattern_match(entry->d_name, str))
			build_files_list(&array_list, entry->d_name);
		entry = readdir(dir);
	}
	free(str);
	closedir(dir);
	if (array_list == NULL)
		return (NULL);
	sort_array(&array_list, m);
	array_files = build_array_files(array_list, m);
	return (array_files);
}

char	*build_array_files(t_list *array_list, t_m *m)
{
	m->ptr = array_list;
	m->k = ft_strlen(m->ptr->content) + 3;
	while (m->ptr != NULL)
	{
		m->k = m->k + ft_strlen(m->ptr->content) + 3;
		m->ptr = m->ptr->next;
	}
	m->new = (char *)malloc(sizeof(char) * m->k + 1);
	if (!m->new)
		return (NULL);
	m->ptr = array_list;
	m->k = 0;
	while (m->ptr != NULL)
	{
		m->new[m->k++] = m->sign;
		m->j = 0;
		while (((char *)m->ptr->content)[m->j] != '\0')
			m->new[m->k++] = ((char *)m->ptr->content)[m->j++];
		m->new[m->k++] = ' ';
		m->ptr = m->ptr->next;
	}
	m->new[m->k] = '\0';
	free_t_list(&array_list);
	return (m->new);
}

void	build_files_list(t_list **list, char *file)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->content = ft_strdup(file);
	if (*list == NULL)
	{
		*list = new_node;
		new_node = *list;
		new_node->next = NULL;
	}
	else if (*list != NULL)
	{
		new_node->next = *list;
		*list = new_node;
	}
}
