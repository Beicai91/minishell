/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:09:26 by bcai              #+#    #+#             */
/*   Updated: 2024/05/17 13:21:40 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(char *msg, t_cmd *cmd)
{
	printf("%s\n", msg);
	free_memory(cmd);
}

char	*join_free_all(char *s1, char *s2, t_cmd *cmd)
{
	char	*temp;

	temp = minishell_strjoin(s1, s2, cmd);
	free(s1);
	s1 = NULL;
	free(s2);
	s2 = NULL;
	return (temp);
}

char	*minishell_strjoin(char const *s1, char const *s2, t_cmd *cmd)
{
	int		len;
	char	*join;

	len = ft_strlen(s1) + ft_strlen(s2);
	join = safe_malloc(len + 1, CHAR, cmd);
	ft_strlcpy(join, s1, len + 1);
	ft_strlcat(join, s2, len + 1);
	return (join);
}

char	*m_sub(char const *s, unsigned int start, size_t len,
		t_cmd *cmd)
{
	char	*sub;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	sub = safe_malloc(len + 1, CHAR, cmd);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}

void	add_qflag(t_qflag **lst, t_qflag *new)
{
	t_qflag	*temp;

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
